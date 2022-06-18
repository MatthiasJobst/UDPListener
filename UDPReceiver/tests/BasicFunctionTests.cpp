#include "CppUTest/TestHarness.h"
#include "src/UDPReceiver.hpp"
extern "C"
{
   #include "NetworkSpy.h"
   #include "SocketSpy.h"
}

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

TEST_GROUP(BasicsTestGroup)
{
   UDPReceiver *receiver;
   struct addrinfo hints;
   struct addrinfo storage;
   struct addrinfo *spy_ai;
   struct sockaddr ai_addr;

   void setup()
   {
      set_addrinfo_null(&hints);
      set_addrinfo_null(&storage);

      spy_ai = &storage;
      spy_ai->ai_addr = &ai_addr;
      spy_ai->ai_next = NULL;
      NetworkSpy_Create(&spy_ai);
      SocketSpy_Create();
   }

   void teardown()
   {
      delete receiver;
      NetworkSpy_Destroy();
      SocketSpy_Destroy();
   }
};

TEST(BasicsTestGroup, InitTest)
{
   receiver = new UDPReceiver(&hints);

   LONGS_EQUAL(hints.ai_flags, AI_PASSIVE);
   LONGS_EQUAL(hints.ai_family, AF_INET);
   LONGS_EQUAL(hints.ai_socktype, SOCK_DGRAM);
   LONGS_EQUAL(hints.ai_protocol, 0);
}

TEST(BasicsTestGroup, CreateSocketForPortTest)
{
   const char *port = "1224";
   NetworkSpy_Set_Pass();
   receiver = new UDPReceiver(&hints);
   CHECK(receiver->createSocketForPort(port));
   LONGS_EQUAL(0, NetworkSpy_get_error());
}

TEST(BasicsTestGroup, CreateSocketForPortTestFail)
{
   const char *port = "*";
   NetworkSpy_Set_Fail(NO_RECOVERY);
   receiver = new UDPReceiver(&hints);
   CHECK(!receiver->createSocketForPort(port));
   LONGS_EQUAL(NO_RECOVERY, NetworkSpy_get_error());
}