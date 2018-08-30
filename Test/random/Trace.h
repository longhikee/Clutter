#ifndef TRACE_H
#define TRACE_H

#define DEBUG false
#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1):__FILE__)
#define TRACE(functionName, info) \
                if(DEBUG) cout << __FILE__ << ":" <<  __LINE__ << " " << functionName << info <<endl
#define TRACE_ERROR(info) \
                cout << __FILENAME__ << ":" <<  __LINE__ << " " << info << endl

#endif
