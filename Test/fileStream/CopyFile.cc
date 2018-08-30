#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
  if (argc < 3)
  {
    cout << "usage: " << endl << "copy file + output file" << endl;
    return -1;
  }

  string inFileName(argv[1]);
  string outFileName(argv[2]);

  ifstream infile(inFileName);
  if(!infile)
  {
    cout << "file open fail" << endl;
    return -1;
  }

  ofstream outfile(outFileName);
  if(!outfile)
  {
    cout << "file open fail" << endl;
    return -1;
  }

  string data;
  while(infile >> data)  //when input file is big, efficient is low
  {
    cout << data << endl; //infile >> data will break in blank space and newline
    outfile << data << endl;      //so this copy will miss them
  }

  infile.close();
  outfile.close();

  return 0;

}
