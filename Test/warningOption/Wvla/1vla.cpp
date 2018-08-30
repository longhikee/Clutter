#include <iostream>
#include <string>
using namespace std;
int main()
{
    string s = "123";
//    int len = s.length();
//    int len = 0;
    char* str = new char[s.length()];

    delete [] str;
    //len = 3;
}
