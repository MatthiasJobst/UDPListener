#ifndef D_NETWORK_SPY_H
#define D_NETWORK_SPY_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

void NetworkSpy_Create(struct addrinfo **);
void NetworkSpy_Destroy(void);

void NetworkSpy_Set_Pass(void);
void NetworkSpy_Set_Fail(int error);
int NetworkSpy_get_error(void);

#endif