#include "NetworkSpy.h"
#include <string.h>
#include <stdio.h>

struct addrinfo **address;
int fail = 0;
int error_no = NETDB_SUCCESS;

void NetworkSpy_Create(struct addrinfo **net_ai)
{
    address = net_ai;
    fail = NETDB_SUCCESS;
    error_no = NETDB_SUCCESS;
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

int NetworkSpy_get_error()
{
    return error_no;
}

int getaddrinfo(const char *hostname, const char *servname, const struct addrinfo *hints, struct addrinfo **res)
{
    *res = *address;

    return fail;
}

void freeaddrinfo(struct addrinfo *ai)
{
    address = NULL;
}

const char *gai_strerror(int error)
{
    error_no = error;
    return "Test";
}