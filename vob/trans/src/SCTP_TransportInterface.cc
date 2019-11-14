#include "SCTP_TransportInterface.h"

SCTP_TransportInterface::SCTP_TransportInterface(const int& fd, const vector<IpAddress>& localAddr) :
    TransportInterface(fd),
    sctpLocalAddr(localAddr),
    currentStreams(0),
    maxStreams(1)
{
}

SCTP_TransportInterface::SCTP_TransportInterface(const vector<IpAddress>& localAddr) :
    TransportInterface(-1),
    sctpLocalAddr(localAddr),
    currentStreams(0),
    maxStreams(1)
{
}

SCTP_TransportInterface::SCTP_TransportInterface(const vector<IpAddress>& localAddr, const vector<IpAddress>& remoteAddr) :
    TransportInterface(-1),
    sctpLocalAddr(localAddr),
    sctpRemoteAddr(remoteAddr),
    currentStreams(0),
    maxStreams(1)
{
}

SCTP_TransportInterface::SCTP_TransportInterface(const int& fd, const IpAddress& localAddr) :
    TransportInterface(fd),
    currentStreams(0),
    maxStreams(1)
{
    sctpLocalAddr.push_back(localAddr);
}

SCTP_TransportInterface::SCTP_TransportInterface(const IpAddress& localAddr) :
    TransportInterface(-1),
    currentStreams(0),
    maxStreams(1)
{
  sctpLocalAddr.push_back(localAddr);
}

SCTP_TransportInterface::SCTP_TransportInterface(const IpAddress& localAddr, const IpAddress& remoteAddr) :
    TransportInterface(-1),
    currentStreams(0),
    maxStreams(1)
{
    sctpLocalAddr.push_back(localAddr);
    sctpRemoteAddr.push_back(remoteAddr);
}

reErrId SCTP_TransportInterface::createSocket()
{
    sockfd = ::socket(localAddress.getFamily(), SOCK_STREAM, IPPROTO_SCTP);
    if (sockfd < 0)
    {
        Log("create socket fail, errno=" << errno);
        return RC_ERROR_INTERNAL;
    }
    return RC_SUCCESS;
}

reErrId SCTP_TransportInterface::bind()
{
    setSCTPOpt();
    const sockaddr_storage& primaryLocalAddr = sctpLocalAddr[0].getSockAddr();
    struct sockaddr* secAddr = NULL;
    int numSecAddr = sctpLocalAddr.size() - 1;
    int ret = 0;

    if (AF_INET == primaryLocalAddr.ss_family)
    {
        secAddr = (struct sockaddr*) new sockaddr_in[numSecAddr];
        ret = ::bind(sockfd, (sockaddr*)(&primaryLocalAddr), sizeof(sockaddr_in));
    }
    else
    {
        secAddr = (struct sockaddr*) new sockaddr_in6[numSecAddr];
        ret = ::bind(sockfd, (sockaddr*)(&primaryLocalAddr), sizeof(sockaddr_in6));
    }
    if (ret < 0)
    {
        Log("bind fail, errno=" << errno);
        if (secAddr)
        {
            delete [] secAddr;
        }
        return RC_ERROR_INTERNAL;
    }

    for (unsigned i = 1; i < sctpLocalAddr.size(); i++)
    {
      const sockaddr_storage& secLocalAddr = sctpLocalAddr[i].getSockAddr();
      if (AF_INET == secLocalAddr.ss_family)      
      {
         memcpy((void*) &secAddr[i-1], (struct sockaddr*) &secLocalAddr, sizeof(sockaddr_in));
      }
      else
      {
         memcpy((void*) &secAddr[i-1], (struct sockaddr*) &secLocalAddr, sizeof(sockaddr_in6));
      }
    }
    if (numSecAddr > 0)
    {
        ret = ::sctp_bindx(sockfd, secAddr, numSecAddr, SCTP_BINDX_ADD_ADDR);
        if (ret < 0)
        {
            Log("bind second paths fail, socket:" << sockfd << " errno=" << errno);
            //to do bindx err handling
        }
    }

    if (secAddr)
    {
        delete [] secAddr;
    }
    return RC_SUCCESS;
}

reErrId SCTP_TransportInterface::connect()
{
    const unsigned numAddr = sctpRemoteAddr.size();
    struct sockaddr* remoteAddr = NULL;

    if (AF_INET == sctpRemoteAddr[0].getSockAddr().ss_family)
    {
        remoteAddr = (struct sockaddr*) new sockaddr_in[numAddr];
    }
    else
    {
        remoteAddr = (struct sockaddr*) new sockaddr_in6[numAddr];
    }

    for (unsigned i = 0; i < numAddr; i++)
    {
        const struct sockaddr_storage& addr = sctpRemoteAddr[i].getSockAddr();
        if (AF_INET == addr.ss_family)
        {
            memcpy((void*) &remoteAddr[i], (struct sockaddr*) &addr, sizeof(sockaddr_in));
        }
        else
        {
            memcpy((void*) &remoteAddr[i], (struct sockaddr*) &addr, sizeof(sockaddr_in6));
        }

    }

    sctp_assoc_t aid;
    int ret = ::sctp_connectx(sockfd, remoteAddr, numAddr, &aid);
    if (ret < 0)
    {
        Log("sctp connect fail, errno=" << errno);
        return RC_ERROR_NETWORK;
    }
    if (remoteAddr)
    {
        delete [] remoteAddr;
    }
    return RC_SUCCESS;
}

ssize_t SCTP_TransportInterface::socketSend(const char* msg, const size_t& len, int& err)
{
    currentStreams = currentStreams % maxStreams;
    struct sctp_sndrcvinfo sinfo = { 0 };
    sinfo.sinfo_stream = currentStreams;
    ssize_t ret = ::sctp_send(sockfd, msg, len, &sinfo, 0);
    if (ret <= 0)
    {
        err = errno;
    }
    else if(ret == len)
    {
        currentStreams++;
    }
    return ret;
}

ssize_t SCTP_TransportInterface::socketReceive(char* msg, const size_t& len, int& err)
{
    struct sockaddr_storage fromAddr;
    socklen_t fromlen = sizeof(fromAddr);
    struct sctp_sndrcvinfo sinfo;
    int msgFlags = 0;
    memset((void*) &fromAddr, 0, sizeof(fromAddr));
    memset((void*) &sinfo, 0, sizeof(sinfo));

    ssize_t ret = ::sctp_recvmsg(sockfd, msg, len, (struct sockaddr*) &fromAddr,
                                   &fromlen, &sinfo, &msgFlags);
    if (ret <= 0)
    {
        err = errno;
    }
    else if (msgFlags & MSG_NOTIFICATION)
    {
        //to do
        Log("recieve sctp notification!");
        err = -1;
        ret = 0;
    }
    return ret;
}

reErrId SCTP_TransportInterface::startServer()
{
    if (RC_SUCCESS != createSocket() || RC_SUCCESS != bind() || RC_SUCCESS != listen())
    {
        return RC_ERROR_INTERNAL;
    }
    return RC_SUCCESS;
}

reErrId SCTP_TransportInterface::startClient()
{
    if (RC_SUCCESS != createSocket() || RC_SUCCESS != bind())
    {
        Log("start Client fail");
        return RC_ERROR_INTERNAL;
    }
    int ret = connect();    //non-block mode, connect will return -1 errno=EINPROGRESS, and TCP establish is going on.
    int err = errno;
    Log("connect ret:" << ret << "  errno:" << errno);

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

void SCTP_TransportInterface::setSCTPOpt()
{
    setAddrParam();
    setRto();
    setAssoc();
    setSackInfo();
    setInitmsg();
}

void SCTP_TransportInterface::setAddrParam()
{
    struct sctp_paddrparams oldParam;
    memset(&oldParam, 0, sizeof(sctp_paddrparams));
    socklen_t len = sizeof(struct sctp_paddrparams);
    int ret = 0, err = 0;
    ret = ::sctp_opt_info(sockfd, 0, SCTP_PEER_ADDR_PARAMS, &oldParam, &len);
    if (ret < 0)
    {
        err = errno;
        Log("sctp_opt_info fail, errno=" << err);
    }
    oldParam.spp_hbinterval = sctpParam.sppaddr.spp_hbinterval;
    oldParam.spp_pathmaxrxt = sctpParam.sppaddr.spp_pathmaxrxt;
    oldParam.spp_flags |= (SPP_HB_ENABLE | SPP_PMTUD_ENABLE);
    ret = ::setsockopt(sockfd, IPPROTO_SCTP, SCTP_PEER_ADDR_PARAMS, &oldParam, sizeof(struct sctp_paddrparams));
    if (ret < 0)
    {
        err = errno;
        Log("setsockopt sctp_paddrparams fail, errno=" << err);
    }
}

void SCTP_TransportInterface::setRto()
{
    int ret = ::setsockopt(sockfd, IPPROTO_SCTP, SCTP_RTOINFO, &sctpParam.rtoinfo, sizeof(struct sctp_rtoinfo));
    if (ret < 0)
    {
        Log("setsockopt sctp_rtoinfo fail, errno=" << errno);
    }
}

void SCTP_TransportInterface::setAssoc()
{
    if (sctpParam.assoc.sasoc_asocmaxrxt > 2 * sctpParam.sppaddr.spp_pathmaxrxt)
    {
        sctpParam.assoc.sasoc_asocmaxrxt = 2 * sctpParam.sppaddr.spp_pathmaxrxt;
    }
    int ret = ::setsockopt(sockfd, IPPROTO_SCTP, SCTP_ASSOCINFO, &sctpParam.assoc, sizeof(struct sctp_assocparams));
    if (ret < 0)
    {
        Log("setsockopt sctp_assocparams fail, errno=" << errno);
    }
}

void SCTP_TransportInterface::setSackInfo()
{
    int ret = ::setsockopt(sockfd, IPPROTO_SCTP, SCTP_DELAYED_SACK, &sctpParam.sackInfo, sizeof(struct sctp_sack_info));
    if (ret < 0)
    {
        Log("setsockopt sctp_sack_info fail, errno=" << errno);
    }
}

void SCTP_TransportInterface::setInitmsg()
{
    int ret = ::setsockopt(sockfd, IPPROTO_SCTP, SCTP_INITMSG, &sctpParam.streams, sizeof(struct sctp_initmsg));
    if (ret < 0)
    {
        Log("setsockopt sctp_initmsg fail, errno=" << errno);
    }
}
