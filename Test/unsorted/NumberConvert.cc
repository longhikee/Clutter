#include <iostream>
using namespace std;
class NumberConvert
{
public:
    NumberConvert()
    {
        cout << "NumberConvert()" << endl;
    }
    virtual ~NumberConvert()
    {
        cout << "~NumberConvert()" << endl;
    }
    void print(char a)
    {
        cout << "char " << a << endl;
    }
    void print(unsigned char a)
    {
        cout << "unsigned char " << a << endl;
    }
    void print(int a)
    {
        cout << "int " << a << endl;
    }
    void print(unsigned int a)
    {
        cout << "unsigned int " << a << endl;
    }
    void print(long a)
    {
        cout << "long " << a << endl;
    }
    void print(unsigned long a)
    {
        cout << "unsigned long " << a << endl;
    }
    void print(long long a)
    {
        cout << "long long " << a << endl;
    }
};

int main()
{
    NumberConvert a;

    a.print(4294967295);//0XFFFFFFFF
    a.print(0XFFFFFFFF);//4294967295

    a.print(0xF0F0F0);

    a.print(0xF0000000);//4026531840
    a.print(4026531840);//0xF0000000

    return 0;
}
