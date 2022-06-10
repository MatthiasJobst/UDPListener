#ifndef SOCKETSPY_C
#define SOCKETSPY_C

#include <sys/socket.h>

     int socket(int, int, int);
     int bind(int, const struct sockaddr *, socklen_t);

#endif