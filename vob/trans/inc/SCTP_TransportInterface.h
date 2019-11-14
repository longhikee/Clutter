#ifndef SCTP_TRANSPORTINTERFACE_H
#define SCTP_TRANSPORTINTERFACE_H
#include <netinet/in.h>
#include <vector>
#include <string.h>
//#include <netinet/sctp.h>
#include "sctp.h"

#include "TransportInterface.h"

using std::vector;

#define DEFAULT_HEARTBEAT_INTERVAL_SCTP 30000
#define DEFAULT_RTO_MIN_SCTP 500
#define DEFAULT_RTO_MAX_SCTP 2000
#define DEFAULT_RTO_INITIAL_SCTP 2000
#define DEFAULT_ASSOC_MAX_RETRANS_SCTP 6
#define DEFAULT_PATH_MAX_RETRANS_SCTP 3
#define DEFAULT_INSTREAMS_SCTP 32
#define DEFAULT_OSTREAMS_SCTP 32
#define DEFAULT_SACK_TIMEOUT_SCTP 200

class SCTP_TransportInterface : public TransportInterface
{
public:
    SCTP_TransportInterface(const int& fd, const vector<IpAddress>& localAddr);
    SCTP_TransportInterface(const vector<IpAddress>& localAddr);
    SCTP_TransportInterface(const vector<IpAddress>& localAddr, const vector<IpAddress>& remoteAddr);
    SCTP_TransportInterface(const int& fd, const IpAddress& localAddr);
    SCTP_TransportInterface(const IpAddress& localAddr);
    SCTP_TransportInterface(const IpAddress& localAddr, const IpAddress& remoteAddr);
    virtual reErrId startServer();
    virtual reErrId startClient();
    void setSCTPOpt();


protected:
    virtual reErrId createSocket();
    virtual reErrId bind();
    virtual reErrId connect();
    virtual ssize_t socketSend(const char* msg, const size_t& len, int& err);
    virtual ssize_t socketReceive(char* msg, const size_t& len, int& err);

private:
    SCTP_TransportInterface();
    SCTP_TransportInterface(SCTP_TransportInterface&);

    class SCTP_Parameter
    {
    public:
        SCTP_Parameter()
        {
            memset(&sppaddr, 0, sizeof(sctp_paddrparams));
            memset(&rtoinfo, 0, sizeof(sctp_rtoinfo));
            memset(&assoc, 0 , sizeof(sctp_assocparams));
            memset(&streams, 0 , sizeof(sctp_initmsg));
            memset(&sackInfo, 0 ,sizeof(sctp_sack_info));

            sppaddr.spp_hbinterval = (unsigned) DEFAULT_HEARTBEAT_INTERVAL_SCTP;
            sppaddr.spp_pathmaxrxt = DEFAULT_PATH_MAX_RETRANS_SCTP;

            rtoinfo.srto_initial = DEFAULT_RTO_INITIAL_SCTP;
            rtoinfo.srto_min = DEFAULT_RTO_MIN_SCTP;
            rtoinfo.srto_max = DEFAULT_RTO_MAX_SCTP;

            assoc.sasoc_asocmaxrxt = DEFAULT_ASSOC_MAX_RETRANS_SCTP;

            streams.sinit_num_ostreams = DEFAULT_OSTREAMS_SCTP;
            streams.sinit_max_instreams = DEFAULT_INSTREAMS_SCTP;

            sackInfo.sack_delay = DEFAULT_SACK_TIMEOUT_SCTP;
        }

        struct sctp_paddrparams sppaddr;
        struct sctp_rtoinfo rtoinfo;
        struct sctp_assocparams assoc;
        struct sctp_initmsg streams;
        struct sctp_sack_info sackInfo;

    };

    void setAddrParam();
    void setRto();
    void setAssoc();
    void setSackInfo();
    void setInitmsg();

    vector<IpAddress> sctpLocalAddr; //first element is primary path, others are second
    vector<IpAddress> sctpRemoteAddr;//first element is primary path, others are second
    unsigned currentStreams;
    unsigned maxStreams;


public:
    SCTP_Parameter sctpParam;

};
#endif
