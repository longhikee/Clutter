#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
//using namespace std;

using std::cout;
using std::endl;
using std::string;
using std::ofstream;
using std::to_string;
using std::ios;

#define _K 1024
const char* baseName = "ostr_";
static unsigned long num = 0;
int main()
{
  char tmp[2 * _K] = {0};

  for (int i = 0; i < _K; i++)
  {
    tmp[i] = i%256 * 5 * 3;
  }
  tmp[2 * _K - 1] = '*';
  
  string fileName;
  char* oss = new char[2 * 10 * _K * _K];
  for (unsigned i = 0; i < _K * 10 ; i++)
  {
    memcpy(oss + i * 2 * _K, tmp, 2 * _K);
  }

  do
  {
    fileName = baseName + to_string(num);
    cout << fileName << endl;
    int big = 10;
    ofstream file(fileName, ios::app | ios::binary);
    do{
    file.seekp(ios::end);
    file.write(oss, 2 * 10 * _K * _K);
    big--;
    }while(big >0);
    
    num++;
  }while(0);

  return 0;
}
