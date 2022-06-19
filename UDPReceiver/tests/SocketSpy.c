#include "SocketSpy.h"
#include <string.h>

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

ssize_t recvfrom(int socket, void *restrict buffer, size_t length, int flags, struct sockaddr *restrict address,
         socklen_t *restrict address_len)
{
    if (failure == FAIL_RECV)
        return -1;

    char buf[9] = "Testdata\n";
    if (buffer != NULL)
        memcpy(buffer, &buf, 9);
    return 9;
}