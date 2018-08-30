#include<iostream>
using namespace std;
int main(int argc, char* argv[])
{
    if(argc > 1)
    {
        return 1;
    }
    char mcc[5]={0};
    char mnc[5]={0};
    char digit_buf[32]="2f810";
    {
        int l_j = 0;
        mcc[l_j] = (int)(digit_buf[0] & 0x0F) + 0x0030;
        l_j++;
        mcc[l_j] = ((int)(digit_buf[0] & 0xF0) >> 4) + 0x0030;
        l_j++;
        mcc[l_j] = (int)(digit_buf[1] & 0x0F) + 0x0030;
        l_j++;
        mcc[l_j] = '\0';


        l_j = 0;
        mnc[l_j] = (int)(digit_buf[2] & 0x0F) + 0x0030;
        l_j++;
        mnc[l_j] = ((int)(digit_buf[2] & 0xF0) >> 4) + 0x0030;
        l_j++;
        mnc[l_j] = ((int)(digit_buf[1] & 0xF0) >> 4) + 0x0030;

        if (mnc[l_j] != 0x000f + 0x0030)
        {
            l_j++;
        }

        mnc[l_j] = '\0';
    }

    cout<<"MCC="<<mcc<<endl;
    cout<<"MNC="<<mnc<<endl;

    return 0;
}
