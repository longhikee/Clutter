#include <iostream>
#include "Trace.h"
using namespace std;

#define DEBUG_LEVEL 0

#define TRC_TRACE_TO_SCREEN()           \
  Trace::redirect_output(cout)

#define TRC_TRACE_TO_FILE(ostream_file) \
  Trace::redirect_output(ostream_file)

#define TRC_RESTORE_TRACE()             \
  Trace::restore_output()

#define TRC_FILE_LINE                   \
        __FILE__ " [" << __LINE__ << "]" << "    "

#define TRC_TRACE_INIT()                \
  Trace

#define TRC_TRACE(message)                     \
  {                                            \
    Trace* trc_ptr = Trace::get_instance();    \
    if (trc_ptr && trc_ptr->is_trace_on())     \
    {                                          \
      *trc_ptr                                 \
      << TRC_FILE_LINE                         \
      << message;                              \
      trc_ptr->write_trace();                  \
    }                                          \
  }
#if DEBUG_LEVEL
  #define TRC_INFO(message)               \
    TRC_TRACE(message)
#else
  #define TRC_INFO(message) ;
#endif


#define TC_TAG(tag) "[" #tag "] "

#define TRC_ERR(message)                \
  TRC_TRACE(TC_TAG(ERR)<< message)

#define TRC_WARN(message)               \
  TRC_TRACE(TC_TAG(WAR) << message)


