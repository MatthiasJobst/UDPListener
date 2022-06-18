#ifndef SOCKETSPY_C
#define SOCKETSPY_C

#include <sys/socket.h>

void SocketSpy_Create(void);
void SocketSpy_Destroy(void);

int socket(int, int, int);
int bind(int, const struct sockaddr *, socklen_t);

#endif