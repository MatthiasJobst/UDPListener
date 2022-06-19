#include "CppUTest/TestHarness.h"
#include "src/UDPReceiver.hpp"
#include "src/UDPReceiverError.hpp"
#include "ErrorHandlerSpy.hpp"

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
   ErrorHandlerSpy *error_handler;
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

      receiver = new UDPReceiver(&hints);
      error_handler = new ErrorHandlerSpy();
      receiver->set_error_handler(error_handler);
   }

   void teardown()
   {
      delete receiver;
      delete error_handler;
      NetworkSpy_Destroy();
      SocketSpy_Destroy();
   }
};

TEST(BasicsTestGroup, InitTest)
{
   LONGS_EQUAL(hints.ai_flags, AI_PASSIVE);
   LONGS_EQUAL(hints.ai_family, AF_INET);
   LONGS_EQUAL(hints.ai_socktype, SOCK_DGRAM);
   LONGS_EQUAL(hints.ai_protocol, 0);
}

TEST(BasicsTestGroup, CreateSocketForPortTest)
{
   const char *port = "1224";
   NetworkSpy_Set_Pass();
   CHECK(receiver->createSocketForPort(port));
   LONGS_EQUAL(0, NetworkSpy_get_error());
   POINTERS_EQUAL(nullptr, error_handler->get_area());
}

TEST(BasicsTestGroup, CreateSocketForPortTestFail)
{
   const char *port = "*";
   NetworkSpy_Set_Fail(NO_RECOVERY);
   CHECK(!receiver->createSocketForPort(port));
   LONGS_EQUAL(NO_RECOVERY, NetworkSpy_get_error());
   STRCMP_EQUAL("getaddrinfo", error_handler->get_area());
}

TEST(BasicsTestGroup, CreateSocketForPortSocketFailTest)
{
   const char *port = "1224";
   NetworkSpy_Set_Pass();
   SocketSpy_Set_FAIL(FAIL_SOCKET);
   CHECK(!receiver->createSocketForPort(port));
   LONGS_EQUAL(0, NetworkSpy_get_error());
   STRCMP_EQUAL("loop", error_handler->get_area());
}

TEST(BasicsTestGroup, CreateSocketForPortBindFailTest)
{
   const char *port = "1224";
   NetworkSpy_Set_Pass();
   SocketSpy_Set_FAIL(FAIL_BIND);
   CHECK(!receiver->createSocketForPort(port));
   LONGS_EQUAL(0, NetworkSpy_get_error());
   STRCMP_EQUAL("loop", error_handler->get_area());
}

TEST(BasicsTestGroup, ReceivePacketTest)
{
   const char *port = "1224";
   NetworkSpy_Set_Pass();
   CHECK(receiver->createSocketForPort(port));
   LONGS_EQUAL(0, NetworkSpy_get_error());
   POINTERS_EQUAL(nullptr, error_handler->get_area());
   const char *input = "No___data";
   SocketSpy_Set_FAIL(NO_FAIL);
   const char *buffer = receiver->receivePacket(&input);
   STRCMP_EQUAL("Testdata", buffer);
}

TEST(BasicsTestGroup, ReceivePacketFailTest)
{
   const char *port = "1224";
   NetworkSpy_Set_Pass();
   CHECK(receiver->createSocketForPort(port));
   LONGS_EQUAL(0, NetworkSpy_get_error());
   POINTERS_EQUAL(nullptr, error_handler->get_area());
   const char *input = "No___data";
   SocketSpy_Set_FAIL(FAIL_RECV);
   const char *buffer = receiver->receivePacket(&input);
   STRCMP_EQUAL("Testdata", buffer);
}