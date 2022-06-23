//
//  UDPReceiver.hpp
//  HomeDashboard
//
//  Created by Matthias Jobst on 07.12.21.
//  Copyright © 2021 Matthias Jobst. All rights reserved.
//

#ifndef UDPReceiver_hpp
#define UDPReceiver_hpp

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "WithErrorHandler.hpp"

#define MAXBUFLEN 9

class UDPReceiver: public WithErrorHandler {
public:
    UDPReceiver(addrinfo *hints);
    bool createSocketForPort(const char *);
    const char *receivePacket(const char **);
    void set_error_handler(ErrorHandler *);

private:
    int sockfd;
    ErrorHandler *error_handler;
    struct addrinfo *hints, *servinfo;
    long numbytes;
    struct sockaddr_storage their_addr;
    char buf[MAXBUFLEN];
    socklen_t addr_len;
    char s[INET6_ADDRSTRLEN];

    void *get_in_addr(struct sockaddr *);
    bool validInfoGottenForPort(const char *port);
    bool isSocketCreatedForAddrInfo(struct addrinfo *);
    bool isSocketBound(struct addrinfo *);
};
#endif /* UDPReceiver_hpp */
