#include "CppUTest/TestHarness.h"
extern "C"
{
    #include "NetworkSpy.h"
}

TEST_GROUP(NetworkSpyTestGroup)
{
    struct addrinfo *test_ai;
    const char *hostname = "127.0.0.1";
    const char *servname = "localhost";
    struct addrinfo hints;
    struct addrinfo *res = NULL;

    void setup()
    {
        NetworkSpy_Create(&test_ai);
    }

    void teardown()
    {
        NetworkSpy_Destroy();
    }
};

TEST(NetworkSpyTestGroup, InitTest)
{
    NetworkSpy_Set_Pass();
    LONGS_EQUAL(0, getaddrinfo(hostname, servname, &hints, &res));
    freeaddrinfo(res);
}

TEST(NetworkSpyTestGroup, AdressTest)
{
    NetworkSpy_Set_Pass();
    LONGS_EQUAL(0, getaddrinfo(hostname, servname, &hints, &res));
    CHECK_COMPARE(res, ==, test_ai);
    freeaddrinfo(res);
}

TEST(NetworkSpyTestGroup, FailTest)
{
    NetworkSpy_Set_Fail(NO_RECOVERY);
    LONGS_EQUAL(NO_RECOVERY, getaddrinfo(hostname, servname, &hints, &res));
    CHECK_COMPARE(res, ==, test_ai);
    freeaddrinfo(res);
}

TEST(NetworkSpyTestGroup, Gai_strerrorTest)
{
    STRCMP_EQUAL("Test", gai_strerror(EAI_SYSTEM));
    LONGS_EQUAL(EAI_SYSTEM, NetworkSpy_get_error());
}