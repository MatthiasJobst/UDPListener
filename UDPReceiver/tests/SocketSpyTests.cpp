#include "CppUTest/TestHarness.h"
extern "C" {
    #include "SocketSpy.h"
}

TEST_GROUP(SocketSpyTestGroup)
{
    struct sockaddr sock;
    socklen_t socklen = sizeof(sock);

    void setup()
    {

    }

    void teardown()
    {

    }
};

TEST(SocketSpyTestGroup, BasicTest)
{
    LONGS_EQUAL(0, socket(0,0,0));
    LONGS_EQUAL(0, bind(0, &sock, socklen));
}