#ifndef UDPSERVERINFO_HPP
#define UDPSERVERINFO_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

class UDPServerInfo
{
public:
    UDPServerInfo(struct addrinfo *);
};
#endif