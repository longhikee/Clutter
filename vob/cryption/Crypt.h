#ifndef CRYPT_H
#define CRYPT_H
#include <string>

using namespace std;


enum Mode
{
  deep,
  quick,
};

class Crypt
{
public:
  Crypt() : m_mode(deep)
  {
  }
  ~Crypt(){};

  void init(const string& in, const string& out);
  bool crypt(const char* inStr, size_t size, char* outStream);
  bool crypt(const string& inStr, string& outStr);
  bool file_handle();

  void set_mode(const Mode& mode);
  void set_key(const char& key);

private:
  Mode m_mode;
  char m_key;
  string m_in_file;
  string m_out_file;
  string m_in_path;
  string m_out_path;


  bool crypt_deep(const char* inStream, const size_t& size, char* outStream);
  bool crypt_deep(const string& inStr, string& outStr);
  bool crypt_quick(const char* inStream, const size_t& size, char* outStream);
  bool crypt_quick(const string& inStr, string& outStr);

  void process_infile(const string& input);
  void process_outfile(const string& output);

};

#endif
