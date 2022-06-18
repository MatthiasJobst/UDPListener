#ifndef SOCKETSPY_C
#define SOCKETSPY_C

#include <sys/socket.h>
#include <unistd.h>

typedef enum {
    NO_FAIL = 0,
    FAIL_SOCKET = 1,
    FAIL_BIND = 2,
} FailConditions_t;

void SocketSpy_Create(void);
void SocketSpy_Destroy(void);

void SocketSpy_Set_FAIL(FailConditions_t);

#endif