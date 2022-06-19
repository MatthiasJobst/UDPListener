#include "SocketHelper.h"
#include <stddef.h>

void set_addrinfo_null(struct addrinfo *address)
{
      address->ai_flags = 0;
      address->ai_family = 0;
      address->ai_socktype = 0;
      address->ai_protocol = 0;
      address->ai_addrlen = 0;
      address->ai_addr = NULL;
      address->ai_canonname = NULL;
      address->ai_next = NULL;
}