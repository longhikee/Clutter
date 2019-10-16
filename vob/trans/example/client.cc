#include <unistd.h>

#include "TCP_TransportInterface.h"

int main()
{
    IpAddress addr(AF_INET, 8888, "127.0.0.1");
    //IpAddress local(AF_INET, 0, "10.67.34.202");
    IpAddress local(AF_INET, 0, "10.67.34.202");
    TCP_TransportInterface client(local, addr);
    if (RC_SUCCESS == client.startClient())
    {
        Log("connect server successfully");
    }
    else
    {
        return -1;
    }
    //option: set non-block mode
    client.setNonBlockSocket();
    const char* msg = "client test";
    if (RC_SUCCESS != client.sendMsg(msg, strlen(msg) + 1))
    {
        Log("send error");
    }
    sleep(2);
    //send fail test
    sleep(10);
    if (RC_SUCCESS != client.sendMsg("resend", 7))
    {
        Log("send error");
    }

    return 0;
}
