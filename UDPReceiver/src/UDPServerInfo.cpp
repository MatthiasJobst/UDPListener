#include "UDPServerInfo.hpp"

UDPServerInfo::UDPServerInfo(struct addrinfo *hints)
{
    serverhints = hints;
    validInfo = false;
    servinfo = nullptr;
}

void UDPServerInfo::set_error_handler(ErrorHandler *handler)
{
    error_handler = handler;
}

struct addrinfo *UDPServerInfo::getServerInfo()
{
    return servinfo;
}

bool UDPServerInfo::validInfoGottenForPort(const char *port)
{
    int rv;
    if ((rv = getaddrinfo(nullptr, port, hints, &servinfo)) != 0) {
        error_handler->addError("getaddrinfo", gai_strerror(rv));
        return false;
    }
    validInfo = true;
    return true;
}