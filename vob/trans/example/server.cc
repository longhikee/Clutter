#include <unistd.h>
#include <memory>

#include "TCP_TransportInterface.h"

using std::shared_ptr;
using std::make_shared;

int main()
{
    IpAddress* addr = new IpAddress(AF_INET, 8888, "127.0.0.1");
    TransportInterface* server = new TCP_TransportInterface(*addr);
    server->startServer();
    int connfd = server->listening();
    if (connfd <= 0)
    {
        return -1;
    }
    //option: set non-block mode
    server->setNonBlockSocket();
    Log("connect client fd=" << connfd);
    shared_ptr<TCP_TransportInterface> responser = make_shared<TCP_TransportInterface>(connfd, *addr);
    //option: set non-block mode
    responser->setNonBlockSocket();
    char data[1024];
    size_t len;
    reErrId ret = responser->recvMsg(data, 1024, len);
    data[len] = '\0';
    if (RC_SUCCESS == ret)
    {
        Log("receive len: " << len << "  msg: " << data);
    }
    else
    {
        Log("recvMsg err: " << ret);
    }
    Log("sleep 10s");
    sleep(10);
    delete addr;
    delete server;

    return 0;
}
