#include "SocketSpy.h"

FailConditions_t failure = NO_FAIL;

void SocketSpy_Create(void)
{
    failure = NO_FAIL;
}

void SocketSpy_Destroy(void)
{
    failure = NO_FAIL;
}

void SocketSpy_Set_FAIL(FailConditions_t fail)
{
    failure = fail;
}

int socket(int domain, int type, int protocol)
{
    if (failure == FAIL_SOCKET)
        return -1;

    return 0;
}

int bind(int socket, const struct sockaddr *address, socklen_t address_len)
{
    if (failure == FAIL_BIND)
        return -1;

    return 0;
}

int close(int socket)
{
    return 0;
}