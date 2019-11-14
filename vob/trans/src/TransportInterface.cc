#include <poll.h>
#include "TransportInterface.h"

#define POLL_TIME_OUT 600000

TransportInterface::TransportInterface(const int& fd) :
    sockfd(fd)
{
}

TransportInterface::TransportInterface(const int& fd, const IpAddress& localAddr) :
    sockfd(fd),
    localAddress(localAddr)
{
}

TransportInterface::TransportInterface(const IpAddress& localAddr) :
    sockfd(-1),
    localAddress(localAddr)
{
}

TransportInterface::TransportInterface(const IpAddress& localAddr, const IpAddress& remoteAddr) :
    sockfd(-1),
    localAddress(localAddr),
    remoteAddress(remoteAddr)
{
}

TransportInterface::~TransportInterface()
{
    close();
}

reErrId TransportInterface::listen()
{
    int ret = ::listen(sockfd, LISTENQ);
    if (ret < 0)
    {
        Log("listen failed, errno=" << errno);
        return RC_ERROR_INTERNAL;
    }
    return RC_SUCCESS;
}

int TransportInterface::accept()
{
    sockaddr addr;
    socklen_t len = sizeof(addr);
    memset(&addr, 0, len);
    int connfd = ::accept(sockfd, &addr, &len);
    if (connfd < 0)
    {
        Log("accept fail, errno=" << errno);
    }
    return connfd;
}

int TransportInterface::listening()
{
    struct pollfd fds[1];
    fds[0].fd = sockfd;
    fds[0].events = POLLIN;
    int pollNum = 1;

    int ret = poll(fds, 1, POLL_TIME_OUT);
    if (-1 == ret)
    {
        Log("poll errno=" << errno);
        return -1;
    }
    else if (0 == ret)
    {
        Log("poll timeout");
        return 0;
    }
    else
    {
        return accept();
    }
}

reErrId TransportInterface::setNonBlockSocket()
{
    //set non-block socket
    if (fcntl(sockfd, F_SETFL, O_NONBLOCK) < 0)
    {
        Log("unable set nonblock socket, errno=" << errno);
        return RC_ERROR_INTERNAL;
    }
    return RC_SUCCESS;
}

reErrId TransportInterface::setSockOpt()
{
    int sockopt = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &sockopt, sizeof(sockopt)) < 0)
    {
        Log("setsockopt( ... SO_REUSEADDR ...) failed, Error ignored. errno=" << errno);
    }
    //to do: set other socket options
    return RC_SUCCESS;
}

void TransportInterface::close()
{
    if (-1 == sockfd)
    {
        return;
    }

    struct linger sockLingerOpt;
    sockLingerOpt.l_onoff = 1;
    sockLingerOpt.l_linger = 0; //Waiting time after CLOSE call in sec

    //if set l_linger=0, it will send abort after call close.

    if (setsockopt(sockfd, SOL_SOCKET, SO_LINGER, &sockLingerOpt, sizeof(sockLingerOpt)) < 0)
    {
        Log("set SO_LINGER fail, errno=" << errno);
        return;
    }


    int ret = ::close(sockfd);
    if (ret < 0)
    {
        Log("close socket: " << sockfd << "fail, errno=" << errno);
    }
}

reErrId TransportInterface::sendMsg(const char* out, const size_t& requestBytes)
{
    size_t left = requestBytes;
    ssize_t nsend = 0;
    int err = 0;
    while (left > 0)
    {
        nsend = socketSend(out, left, err);
        if (nsend <= 0)
        {
            if (EINTR == err)
            {
                continue;
            }
            else if (EAGAIN == err)
            {
                Log("EAGAIN error on Send Socket!");
                //to do EAGAIN re-send handling
                return RC_ERROR_NETWORK;
            }
            else
            {
                Log("send message fail, errno: " << err);
                return RC_ERROR_NETWORK;
            }
        }
        else
        {
            left -= nsend;
            out += nsend;
        }
    }
    return RC_SUCCESS;
}

reErrId TransportInterface::recvMsg(char* data, const size_t& requestBytes, size_t& returnBytes, bool waitComplete)
{
    size_t left = requestBytes;
    ssize_t nread = 0;
    int err = 0;

    returnBytes = 0;
    while (left > 0)
    {
        nread = socketReceive(data, left, err);
        //Log("nread=" << nread);
        if (nread <= 0)
        {
            if (0 == nread)
            {
                if (0 == err)
                {
                    return RC_SUCCESS;
                }
                else
                {
                    Log("errno=" << err);
                    Log("peer had closed connection");
                    return RC_ERROR_NETWORK;
                }
            }
            else if (EINTR == err)
            {
                continue;
            }
            else if (EAGAIN == err)
            {
                //Log("EAGAIN error on Receive Socket!");
                break;
            }
            else
            {
                Log("receive message fail, errno: " << err);
                return RC_ERROR_NETWORK;
            }
        }
        left -= nread;
        data += nread;
        returnBytes += nread;
        if (!waitComplete)
        {
            break;
        }
    }

    return RC_SUCCESS;
}
