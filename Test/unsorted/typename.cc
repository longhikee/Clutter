

class MyArray
{
public:
  typedef int LengthType;
//...
};

template<class T>
void MyMethod(T myattr)
{
  typedef typename T::LengthType LengthType;
  LengthType length = myattr.GetLength;

}
/**
这个时候 typename 的作用就是告诉 c++ 编译器，typename 后面的字符串为一个类型名称，而不是成员函数或者成员变量，这个时候如果前面没有 typename，编译器没有任何办法知道 T::LengthType 是一个类型还是一个成员名称(静态数据成员或者静态函数)，所以编译不能够通过。
**/



