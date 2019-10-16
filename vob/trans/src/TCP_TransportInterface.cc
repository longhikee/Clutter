#include <poll.h>

#include "TCP_TransportInterface.h"

TCP_TransportInterface::TCP_TransportInterface(const int& fd, const IpAddress& localAddr) :
    TransportInterface(fd, localAddr)
{
}

TCP_TransportInterface::TCP_TransportInterface(const IpAddress& localAddr) :
    TransportInterface(localAddr)
{
}

TCP_TransportInterface::TCP_TransportInterface(const IpAddress& localAddr, const IpAddress& remoteAddr) :
    TransportInterface(localAddr, remoteAddr)
{
}

reErrId TCP_TransportInterface::createSocket()
{
    sockfd = ::socket(localAddress.getFamily(), SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0)
    {
        Log("create socket fail, errno=" << errno);
        return RC_ERROR_INTERNAL;
    }
    return RC_SUCCESS;
}

reErrId TCP_TransportInterface::bind()
{
    const sockaddr_storage& localAddr = localAddress.getSockAddr();
    int ret = 0;

    if (AF_INET == localAddr.ss_family)
    {
        ret = ::bind(sockfd, (sockaddr*)(&localAddr), sizeof(sockaddr_in));
    }
    else
    {
        ret = ::bind(sockfd, (sockaddr*)(&localAddr), sizeof(sockaddr_in6));
    }
    if (ret < 0)
    {
        Log("bind fail, errno=" << errno);
        return RC_ERROR_INTERNAL;
    }
    return RC_SUCCESS;
}

reErrId TCP_TransportInterface::connect()
{
    const sockaddr_storage& addr = remoteAddress.getSockAddr();
    int ret = 0;
    if (AF_INET == addr.ss_family)
    {
        ret = ::connect(sockfd, (sockaddr*)&addr, sizeof(sockaddr_in));
    }
    else
    {
        ret = ::connect(sockfd, (sockaddr*)&addr, sizeof(sockaddr_in6));
    }
    if (ret < 0)
    {
        //Log("connect fail, errno=" << errno);
        return RC_ERROR_NETWORK;
    };
    return RC_SUCCESS;
}

ssize_t TCP_TransportInterface::socketSend(const char* msg, const size_t& len, int& err)
{
    ssize_t ret = ::send(sockfd, msg, len, 0);
    if (ret <= 0)
    {
        err = errno;
    }
    return ret;
}

ssize_t TCP_TransportInterface::socketReceive(char* msg, const size_t& len, int& err)
{
    ssize_t ret = ::recv(sockfd, msg, len, 0);
    if (ret <= 0)
    {
        err = errno;
    }
    return ret;
}

reErrId TCP_TransportInterface::startServer()
{
    if (RC_SUCCESS != createSocket() || RC_SUCCESS != bind() || RC_SUCCESS != listen())
    {
        return RC_ERROR_INTERNAL;
    }
    return RC_SUCCESS;
}

reErrId TCP_TransportInterface::startClient()
{
    if (RC_SUCCESS != createSocket() || RC_SUCCESS != bind())
    {
        Log("start Client fail");
        return RC_ERROR_INTERNAL;
    }
    int ret = connect();    //non-block mode, connect will return -1 errno=EINPROGRESS, and TCP establish is going on.
    int err = errno;

    //poll to check if connection is OK.
    struct pollfd fds[1];
    fds[0].fd = sockfd;
    fds[0].events = POLLIN | POLLOUT;
    if (RC_SUCCESS != ret)
    {
        if (EINPROGRESS != err)
        {
            return RC_ERROR_NETWORK;
        }
        else
        {
            while (1)
            {
                ret = poll(fds, 1, 0);
                if (ret < 0) // Handles errors in poll()
                {
                    err = errno;
                    if (EINTR == err || EINPROGRESS == err || EALREADY == err)
                    {
                        continue;
                    }
                }
                else if (0 == ret)
                {
                    Log("connection poll timeout");
                    return RC_ERROR_NETWORK;
                }
                else
                {
                    if (fds[0].events & POLLOUT || fds[0].events & POLLIN)
                    {
                        break;
                    }
                    else
                    {
                        return RC_ERROR_NETWORK;
                    }
                }
            }
        }
    }

    return RC_SUCCESS;
}

