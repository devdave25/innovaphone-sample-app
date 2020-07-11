/*---------------------------------------------------------------------------*/
/* dns.h                                                                     */
/* copyright (c) innovaphone 2015                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

#define DNS_DEFAULT_TIMEOUT 5000

class IDns {
public:
    static IDns * Create(class IIoMux * const iomux);
    virtual ~IDns() {};
    virtual void GetHostByName(const char * host, class UDns * const user, class IInstanceLog * const log, dword timeout = DNS_DEFAULT_TIMEOUT, bool all = false) = 0;
};

class UDns {
public:
    virtual void DnsGetHostByNameResult(const char * addr, bool isIPv6) = 0;
};
