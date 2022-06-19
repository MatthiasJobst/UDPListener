#include "UDPServerInfo.hpp"

struct addrinfo *serverhints;

UDPServerInfo::UDPServerInfo(struct addrinfo *hints)
{
    serverhints = hints;
}