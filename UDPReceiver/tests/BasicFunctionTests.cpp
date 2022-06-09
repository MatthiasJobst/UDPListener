#include "CppUTest/TestHarness.h"
#include "src/UDPReceiver.hpp"
#include "NetworkSpy.h"

UDPReceiver *receiver;
struct addrinfo hints = addrinfo();
struct addrinfo *spy_ai;

TEST_GROUP(BasicsTestGroup)
{
   void setup()
   {
      receiver = new UDPReceiver(&hints);
      NetworkSpy_Create(&spy_ai);
   }

   void teardown()
   {
      delete receiver;
      NetworkSpy_Destroy();
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
}

TEST(BasicsTestGroup, CreateSocketForPortTestFail)
{
   const char *port = "*";
   NetworkSpy_Set_Fail(NO_RECOVERY);
   CHECK(!receiver->createSocketForPort(port));
   LONGS_EQUAL(NO_RECOVERY, NetworkSpy_get_error());
}