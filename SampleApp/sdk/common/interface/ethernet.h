/*---------------------------------------------------------------------------*/
/* ethernet.h                                                                */
/* copyright (c) innovaphone 2016                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

#define MAC_ADDRESS_SIZE    6

class IEthernet {
public:
    static bool GetMACAddress(byte * mac, class IInstanceLog * const log);
};
