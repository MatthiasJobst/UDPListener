#ifndef UDPSERVERINFO_HPP
#define UDPSERVERINFO_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "WithErrorHandler.hpp"

class UDPServerInfo: public WithErrorHandler
{
public:
    UDPServerInfo(struct addrinfo *);
    void set_error_handler(ErrorHandler *);
    struct addrinfo *getServerInfo();
    bool validInfoGottenForPort(const char *);
private:
    ErrorHandler *error_handler;
    struct addrinfo *servinfo;
    struct addrinfo *hints;
    struct addrinfo *serverhints;
    bool validInfo;
};
#endif