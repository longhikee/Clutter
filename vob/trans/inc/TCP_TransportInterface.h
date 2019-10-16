#ifndef TCP_TRANSPORTINTERFACE_H
#define TCP_TRANSPORTINTERFACE_H

#include "TransportInterface.h"


class TCP_TransportInterface : public TransportInterface
{
public:
    TCP_TransportInterface(const int& fd, const IpAddress& localAddr);
    TCP_TransportInterface(const IpAddress& localAddr);
    TCP_TransportInterface(const IpAddress& localAddr, const IpAddress& remoteAddr);
    virtual reErrId startServer();
    virtual reErrId startClient();

protected:
    virtual reErrId createSocket();
    virtual reErrId bind();
    virtual reErrId connect();
    virtual ssize_t socketSend(const char* msg, const size_t& len, int& err);
    virtual ssize_t socketReceive(char* msg, const size_t& len, int& err);

private:
    TCP_TransportInterface();
    TCP_TransportInterface(const TCP_TransportInterface&);

};

#endif
