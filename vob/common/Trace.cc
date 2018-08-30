#include <time.h>
#include <assert.h>
#include <stdio.h>
#include "Trace.h"

ostream* Trace::m_redirected_ptr(0);

Trace::Trace(stringbuf* buf)
  : ostream(buf),
    m_str_buf(buf)
{
}

Trace::~Trace()
{
  if (m_str_buf)
  {
    delete m_str_buf;
  }
}

Trace* Trace::get_instance()
{
  static Trace instance(new stringbuf(ios_base::out));
  return &instance;
}

void Trace::redirect_output(ostream& o)
{
  m_redirected_ptr = &o;
}

void Trace::restore_output()
{
  m_redirected_ptr = 0;
}

bool Trace::is_trace_on()
{
  if (m_redirected_ptr)
  {
    return true;
  }
  return false;
}
void Trace::write_trace()
{
  ends(*this);

  if(!good())
  {
    clear();
  }
  else if(m_redirected_ptr)
  {
    char date_time_str[30] = {0};
    getTimeStamp(date_time_str);
    *m_redirected_ptr << date_time_str << " " << m_str_buf->str().c_str() << endl;

  }

  seekp(0);
}
void Trace::getTimeStamp(char* date_time_str)
{
  time_t rawtime;
  struct tm* timeinfo;

  rawtime = time(NULL);
  timeinfo = localtime(&rawtime);

  sprintf(date_time_str, "%02d-%02d-%d:%02d:%02d:%02d", timeinfo->tm_mday, (timeinfo->tm_mon) + 1,
              (timeinfo->tm_year) + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}
