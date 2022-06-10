#include "SocketSpy.h"

int socket(int domain, int type, int protocol)
{
    return 0;
}

int bind(int socket, const struct sockaddr *address, socklen_t address_len)
{
    return 0;
}