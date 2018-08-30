#include <iostream>
using namespace std;

class ExpMsg
{
  public:
    ExpMsg(const string& msg):b_oldObject(false),m_msg(msg)
    {
      cout << "constructor" << endl;
    }
    ExpMsg(const ExpMsg& expMsg):b_oldObject(false),m_msg(expMsg.m_msg)
    {
      cout << "copy constructor" << endl;
    }
    ~ExpMsg()
    {
      cout << "destructor" << endl;
    }

    std::string m_msg;
    bool b_oldObject;
};

int main()
{
  try
  {
    try
    {
      ExpMsg msg("Exception");
      msg.b_oldObject = true;
      throw msg;
    }
    catch (ExpMsg& msg)
    {
      cout << "inner catch: " << msg.m_msg << ", old=" << msg.b_oldObject << endl;
      msg.b_oldObject = true;
      throw;
    }
    catch (...)
    {
      cout << "inner generic catch" << endl;
    }
  }
  catch (ExpMsg& msg)
  {
    cout << "outter catch: " << msg.m_msg << ", old= " << msg.b_oldObject << endl;
  }
}
