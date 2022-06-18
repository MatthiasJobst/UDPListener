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
        SocketSpy_Create();
    }

    void teardown()
    {
        SocketSpy_Destroy();
    }
};

TEST(SocketSpyTestGroup, BasicTest)
{
    LONGS_EQUAL(0, socket(0,0,0));
    LONGS_EQUAL(0, bind(0, &sock, socklen));
}

TEST(SocketSpyTestGroup, No_Fail_Test)
{
    SocketSpy_Set_FAIL(NO_FAIL);
    LONGS_EQUAL(0, socket(0,0,0));
    LONGS_EQUAL(0, bind(0, &sock, socklen));
}

TEST(SocketSpyTestGroup, Socket_Fail_Test)
{
    SocketSpy_Set_FAIL(FAIL_SOCKET);
    LONGS_EQUAL(-1, socket(0,0,0));
    LONGS_EQUAL(0, bind(0, &sock, socklen));
}

TEST(SocketSpyTestGroup, Bind_Fail_Test)
{
    SocketSpy_Set_FAIL(FAIL_BIND);
    LONGS_EQUAL(0, socket(0,0,0));
    LONGS_EQUAL(-1, bind(0, &sock, socklen));
}

TEST(SocketSpyTestGroup, CloseTest)
{
    LONGS_EQUAL(0, close(1));
}

TEST(SocketSpyTestGroup, RecvfromZeroTest)
{
    LONGS_EQUAL(0, recvfrom(0, NULL, 0, 0, NULL, 0));
}