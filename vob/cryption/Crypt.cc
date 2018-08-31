#include <fstream>
#include <cstring>
#include <stdio.h>
#include "crypt.h"
#include "TraceMacros.h"

#define ONE_K 1024
#define MAX_BLOCK ONE_K * ONE_K * 200

void Crypt::init(const string& in, const string& out)
{
  process_infile(in);
  if (!out.empty())
  {
    process_outfile(out);
  }
}

void Crypt::set_mode(const Mode& mode)
{
  m_mode = mode;
}

void Crypt::set_key(const char& key)
{
  m_key = key;
}

bool Crypt::crypt(const string& inStr, string& outStr)
{
  if (deep == m_mode)
  {
    return crypt_deep(inStr, outStr);
  }
  else if (quick == m_mode)
  {
    return crypt_quick(inStr, outStr);
  }

  TRC_ERR("invalid mode" << m_mode);
  return false;
}

bool Crypt::crypt_deep(const string& inStr, string& outStr)
{
  size_t len = inStr.size();
  outStr.resize(len);
  for (size_t i = 0; i < len ; i++)
  {
    outStr.at(i) = inStr.at(i) ^ m_key;
  }

  return true;
}

bool Crypt::crypt_quick(const string& inStr, string& outStr)
{
  cout << "to do" << endl;
  return false;
}


void Crypt::process_infile(const string& input)
{
  size_t pos = input.find_last_of('\\');
  if (pos != string::npos)
  {
    m_in_file = input.substr(pos + 1, string::npos);
    m_in_path = input.substr(0, pos + 1);
  }
  else
  {
    pos = input.find_last_of('/');
    if (pos != string::npos)
    {
      m_in_file = input.substr(pos + 1, string::npos);
      m_in_path = input.substr(0, pos + 1);
    }
    else
    {
      m_in_file = input;
      m_in_path.clear();
    }
  }
  TRC_INFO("fileName: " << m_in_file);
  TRC_INFO("path: "<< m_in_path);
}

void Crypt::process_outfile(const string& output)
{
  size_t pos = output.find_last_of('\\');
  if (pos != string::npos)
  {
    m_out_file = output.substr(pos + 1, string::npos);
    m_out_path = output.substr(0, pos + 1);
  }
  else
  {
    pos = output.find_last_of('/');
    if (pos != string::npos)
    {
      m_out_file = output.substr(pos + 1, string::npos);
      m_out_path = output.substr(0, pos + 1);
    }
    else
    {
      m_out_file = output;
      m_out_path.clear();
    }
  }
  TRC_INFO("fileName: " << m_out_file);
  TRC_INFO("path: "<< m_out_path);
  if (!m_out_path.empty())
  {
    string cmd = "mkdir " + m_out_path;
    system(cmd.c_str());
  }
}

bool Crypt::file_handle()
{
  string fileIn(m_in_path + m_in_file);
  string fileOut;
  if(m_out_file.empty())
  {
    fileOut = m_out_path + m_in_file + ".cr";
  }
  else
  {
    fileOut = m_out_path + m_out_file;
  }

  string inStr, outStr;
  ifstream inFile(fileIn, ios::binary);

  if(inFile)
  {
    inFile.seekg(0, inFile.end);
    size_t length = inFile.tellg();
    inFile.seekg(0, inFile.beg);

    char* buffer = 0;
    if (length < MAX_BLOCK)
    {
      char* buffer = new char[length];
      inFile.read(buffer, length);
      inFile.close();

      inStr.resize(length);
      memcpy((char*)inStr.c_str(), buffer, length);

      crypt(inStr, outStr);

      ofstream outFile(fileOut, ios::binary);
      if(outFile)
      {
        outFile << outStr;
        TRC_INFO("create out file: " << fileOut);
        outFile.close();
      }
      else
      {
        TRC_ERR("create file "<< fileOut << " failed");
        return false;
      }
    }
    else
    {
      char* buffer = new char[MAX_BLOCK];
      inStr.resize(MAX_BLOCK);
      ofstream outFile(fileOut, ios::binary);
      if (outFile){
      while(true)
      {
        if (length > MAX_BLOCK)
	{
          length -= MAX_BLOCK;
	  inFile.read(buffer, MAX_BLOCK);
	  memcpy((char*)inStr.c_str(), buffer, MAX_BLOCK);
	  crypt(inStr, outStr);
	  outFile << outStr;
        }
	else
	{
	  inFile.read(buffer, length);
	  inFile.close();
	  inStr.clear();
	  inStr.resize(length);
	  memcpy((char*)inStr.c_str(), buffer, length);
	  crypt(inStr, outStr);
	  outFile << outStr;

          break;
	}
      }
    }
    else
    {
      TRC_ERR("create file "<< fileOut << "failed");
      return false;
    }
    }

    if (buffer)
    {
      delete [] buffer;
    }

    inFile.close();
  }
  else
  {
    TRC_ERR("file: "<< fileIn << " noexist");
    return false;
  }

  return true;
}
