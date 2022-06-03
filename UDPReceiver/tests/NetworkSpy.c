#include "NetworkSpy.h"
#include <string.h>
#include <stdio.h>

struct addrinfo **address;
int fail = 0;

void NetworkSpy_Create(struct addrinfo **net_ai)
{
    address = net_ai;
}

void NetworkSpy_Destroy(void)
{
    address = NULL;
}

void NetworkSpy_Set_Pass(void)
{
    fail = NETDB_SUCCESS;
}

void NetworkSpy_Set_Fail(int error)
{
    fail = error;
}

int getaddrinfo(const char *hostname, const char *servname, const struct addrinfo *hints, struct addrinfo **res)
{
    res = address;

    return fail;
}

void freeaddrinfo(struct addrinfo *ai)
{
}