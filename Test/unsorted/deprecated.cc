#include <iostream>
using namespace std;
void func(const char* str)
{
    cout<<str<<endl;

}
int main()
{
    char *filename = "/vob/sdm_hss_sl";
    const char *xml = "/vob/../*.xml";
    func(filename);
    func(xml);
    return 0;
}
