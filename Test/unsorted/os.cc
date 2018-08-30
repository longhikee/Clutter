#include <iostream>
#include <assert.h>
using namespace std;

class SYS_Trace : public ostream
{
  public:
    static ostream*   m_redirected_ptr_s;
    void write_trace(){*m_redirected_ptr_s << "write trace" << endl;};


};

//global function
ostream& trace(ostream& o)
{
  assert(dynamic_cast<SYS_Trace*>(&o));
  ((SYS_Trace&)o).write_trace();
  return o;
}

int main()
{
  SYS_Trace* trc_ptr = new SYS_Trace();
  trc_ptr->m_redirected_ptr_s = &cout;

  *trc_ptr << "message" << trace;
//  trace(*trc_ptr);

}
