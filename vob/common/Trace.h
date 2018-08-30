#ifndef TRACE_H
#define TRACE_H
#include <iostream>
#include <sstream>
using namespace std;

class Trace : public ostream
{
public:
  //to do Lock
  static Trace* get_instance();
  bool is_trace_on();
  void write_trace();

  static void redirect_output(ostream& o);
  static void restore_output();

private:
  static ostream* m_redirected_ptr;
  void getTimeStamp(char* data_time_str);
  stringbuf* m_str_buf;

  Trace(stringbuf* buf);
  virtual ~Trace();

};


#endif
