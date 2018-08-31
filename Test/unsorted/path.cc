#include <iostream>
#include <string>

using namespace std;

int main(int arg, char** argv)
{
/*
  string path("/d/workspace/txt");
  string file;
  size_t pos = path.find_last_of('/');
  if (pos != string::npos)
  {
    file = path.substr(pos + 1, string::npos);
  }
  cout << file << endl;

  path = "D:\\workspace\\txt.txt";
  pos = path.find_last_of('\\');
  if (pos != string::npos)
  {
    file = path.substr(pos + 1, string::npos);
  }

  cout << file << endl;
*/

  string path(argv[1]);
  string PATH;
  string file;
  size_t pos = path.find_last_of('\\');
  if (pos != string::npos)
  {
    file = path.substr(pos + 1, string::npos);
    PATH = path.substr(0, pos + 1);
  }
  else
  {
    cout << path << " not find" << endl;
  }
  cout << "file: " << file << endl;
  cout << "PATH: " << PATH << endl;

  return 0;
}
