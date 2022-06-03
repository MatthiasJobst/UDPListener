#include "NetworkSpy.h"
#include <string.h>
#include <stdio.h>

struct addrinfo **address;

void NetworkSpy_Create(struct addrinfo **net_ai)
{
    address = net_ai;
}

void NetworkSpy_Destroy(void)
{
    address = NULL;
}

int getaddrinfo(const char *hostname, const char *servname, const struct addrinfo *hints, struct addrinfo **res)
{
    printf("\nFake getaddrinfo called!\n");
    res = address;
    return 0;
}

void freeaddrinfo(struct addrinfo *ai)
{
    printf("\nFake freeaddrinfo called!\n");
}