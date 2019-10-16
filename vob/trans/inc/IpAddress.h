#ifndef IP_ADDRESS_H
#define IP_ADDRESS_H
#include <string.h>
#include <string>
#include <sys/types.h>
#include <arpa/inet.h>

using std::string;

class IpAddress
{
private:
    typedef sa_family_t AFamily;
    typedef in_port_t sockPort;
    struct sockaddr_storage sockAddr;
    bool valid;

public:
    IpAddress()
    {
        valid = false;
        memset(&sockAddr, 0, sizeof(sockaddr_storage));
        struct sockaddr_in* addr = (sockaddr_in*) &sockAddr;
        (*addr).sin_family = AF_INET;
        (*addr).sin_port = htons(0);
    }
    IpAddress(const IpAddress& ipAddr)
    {
        memcpy(&sockAddr, &(ipAddr.getSockAddr()), sizeof(sockAddr));
        valid = ipAddr.isValid();
    }
    IpAddress(const AFamily& family, const sockPort& port, const string& ip)
    {
        valid = true;
        memset(&sockAddr, 0, sizeof(sockaddr_storage));
        if (family == AF_INET)
        {
            struct sockaddr_in* addr = (sockaddr_in*) &sockAddr;
            addr->sin_family = family;
            addr->sin_port = htons(port);
            if (1 != inet_pton(family, ip.c_str(), &(addr->sin_addr)))
            {
                valid = false;
            }
        }
        else
        {
            struct sockaddr_in6* addr6 = (sockaddr_in6*) &sockAddr;
            addr6->sin6_family = family;
            addr6->sin6_port = port;
            if (1 != inet_pton(family, ip.c_str(), &(addr6->sin6_addr)))
            {
                valid = false;
            }
        }
    }

    AFamily getFamily() const
    {
        return ((sockaddr_in*) &sockAddr)->sin_family;
    }

    sockPort getPort() const
    {
        return ntohs((*((sockaddr_in*) &sockAddr)).sin_port);
    }

    bool isValid() const
    {
        return valid;
    }

    const sockaddr_storage& getSockAddr() const
    {
        return sockAddr;
    }
};

#endif
