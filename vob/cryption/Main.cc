#include <string>

#include "TraceMacros.h"
#include "Crypt.h"

using namespace std;


void init()
{
  Trace::get_instance();

  TRC_TRACE_TO_SCREEN();
}

int main(int argc, char** argv)
{

  if (argc < 3)
  {
    cout << "usage: " << endl << "key + input + output(could use default)" << endl;
    cout << "e.g: crypt.exe 1 test.txt" << endl;
    cout << "e.g: crypt.exe 1 test.txt out.txt" << endl;
    cout << "e.g: crypt.exe 1 C:\\test\\test.txt D:\\test\\out.txt" << endl;
    return -1;
  }

  init();
  Crypt* crypt = new Crypt();
  if (argc >= 4)
  {
    crypt->init(argv[2], argv[3]);
  }
  else
  {
    crypt->init(argv[2], "");
  }

  if(!crypt)
  {
    TRC_ERR("new Crypt fail");
    return -1;
  }

  int in_key = atoi(argv[1]);
  if (in_key >= 256 || in_key < 0)
  {
    TRC_ERR("key should less than 256 and more than 0");
    return -1;
  }
  else
  {
    int key = in_key;
    TRC_INFO("key: " << key);
    crypt->set_key(key);
  }

  crypt->file_handle();

  if(crypt)
  {
    delete crypt;
  }

  return 0;
}
