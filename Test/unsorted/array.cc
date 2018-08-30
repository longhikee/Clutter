#include <iostream>
using namespace std;
int main()
{/*
    int a[3] = {0,1,2};
    int b[3] = {2,1,0};
    for(int i = 0; i < 3; i++)
    {
        a[i] = b[i];
        cout<<a[i];

    }
*/
/*    unsigned int a = 2;
    unsigned long b = 3;
    int c = 1;
    a = b;
    b = a;
    b = c;
    a = c;

    //char *arr[b] = {0};  error
    char* arr[10] = {0};  //compile pass
*/
    char *array[3] = {"a0","b1","c2"};
    cout<<array[0]<<endl;
    cout<<array[2]<<endl;
    cout<<"sizeof array="<<sizeof(array)<<endl;//24
    cout << "array= " << array << endl;
    cout << "*array= " << *array << endl;

    char tmp[][3] = {"a","b1","c"};
    cout<<tmp[1]<<endl;
    cout<<tmp[1][1]<<endl;

    return 0;
}
