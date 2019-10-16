#ifndef TRANSPORTINTERFACE_H
#define TRANSPORTINTERFACE_H
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "IpAddress.h"


//define log
#include <iostream>
#define Log(x) std::cout << x << std::endl;
//end define log

using std::vector;

const int LISTENQ = 7;

enum reErrId
{
    RC_SUCCESS,
    RC_ERROR_INTERNAL,
    RC_ERROR_NETWORK
};

class TransportInterface
{
public:
    TransportInterface(const int& fd, const IpAddress& localAddr);
    TransportInterface(const IpAddress& localAddr);
    TransportInterface(const IpAddress& localAddr, const IpAddress& remoteAddr);
    virtual reErrId startServer() = 0;
    virtual reErrId startClient() = 0;

    int listening();
    reErrId setSockOpt();
    reErrId setNonBlockSocket();
    reErrId sendMsg(const char* out, const size_t& request_bytes);
    reErrId recvMsg(char* data, const size_t& request_bytes, size_t& return_bytes, bool waitComplete = false);

    virtual ~TransportInterface();

protected:
    virtual reErrId createSocket() = 0;
    virtual reErrId bind() = 0;
    virtual reErrId connect() = 0;

    reErrId listen();
    int accept();
    virtual void close();
    virtual ssize_t socketSend(const char* msg, const size_t& len, int& err) = 0;
    virtual ssize_t socketReceive(char* msg, const size_t& len, int& err) = 0;

    int sockfd;
    IpAddress localAddress;
    IpAddress remoteAddress;

private:
    TransportInterface();
    TransportInterface(const TransportInterface&);
};

#endif
