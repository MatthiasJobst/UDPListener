#ifndef SOCKETHELPER_H
#define SOCKETHELPER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

void set_addrinfo_null(struct addrinfo *);

#endif