//
//  UDPReceiver.cpp
//  HomeDashboard
//
//  Created by Matthias Jobst on 07.12.21.
//  Copyright © 2021 Matthias Jobst. All rights reserved.
//

#include "UDPReceiver.hpp"

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

UDPReceiver::UDPReceiver(addrinfo *addrHints) {
    hints = addrHints;
    memset(hints, 0, sizeof(addrinfo));
    hints->ai_family = AF_INET; // set to AF_INET to use IPv4
    hints->ai_socktype = SOCK_DGRAM;
    hints->ai_flags = AI_PASSIVE; // use my IP
}

bool UDPReceiver::createSocketForPort(const char *portUDP) {
    if ((rv = getaddrinfo(NULL, portUDP, hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 0;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("listener: socket");
            continue;
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("listener: bind");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "listener: failed to bind socket\n");
        return 0;
    }

    freeaddrinfo(servinfo);

    return 1;
}

const char *UDPReceiver::receivePacket(const char **packetAddr){
    addr_len = sizeof their_addr;
    if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0, (struct sockaddr *)&their_addr, &addr_len)) == -1) {
        perror("recvfrom");
        exit(1);
    }
    
    *packetAddr = inet_ntop(their_addr.ss_family,
    get_in_addr((struct sockaddr *)&their_addr),
                         s, sizeof s);
    printf("Address: %s\t", *packetAddr);
    buf[MAXBUFLEN - 1] = '\0';
    printf("MAC: \"");
    for (int i = 0; i < 6; i++)
        printf("%02hhx", buf[i]);
    unsigned int type = buf[6];
    printf("\"\tType: %i\n", type);
    
    return buf;
}
