#include <iostream>
using namespace std;


class Data
{
    friend ostream& operator<<(ostream& o, const Data& d);

public:
    Data();
    ~Data(){}
private:
    int a;
    int b;
    int c;

};

std::ostream& operator<<(ostream& o, const Data& d)
{
    o << "~~~Data~~~";
    o << "\na = " << d.a;
    o << "\nb = " << d.b;
    o << "\nc = " << d.c;
    o << "\n";
}

Data::Data()
{
    a = 1;
    b = 2;
    c = 3;
}

int main()
{
    Data data;
    cout << data;

    return 0;
}
