#include "CppUTest/TestHarness.h"
#include "src/UDPReceiver.hpp"
#include <netdb.h>

UDPReceiver *receiver;
struct addrinfo hints;

TEST_GROUP(BasicsTestGroup)
{
   void setup()
   {
      receiver = new UDPReceiver(&hints);
   }

   void teardown()
   {
      delete receiver;
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
   CHECK(receiver->createSocketForPort(port));
}

TEST(BasicsTestGroup, CreateSocketForPortTestFail)
{
   const char *port = "bullshit";
   CHECK(!receiver->createSocketForPort(port));
}