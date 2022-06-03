#include "CppUTest/TestHarness.h"
#include "NetworkSpy.h"

struct addrinfo *test_ai;

TEST_GROUP(NetworkSpyTestGroup)
{
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
    const char *hostname = "127.0.0.1";
    const char *servname = "localhost";
    struct addrinfo hints;
    struct addrinfo *res;
    LONGS_EQUAL(0, getaddrinfo(hostname, servname, &hints, &res));
    freeaddrinfo(res);
}

TEST(NetworkSpyTestGroup, AdressTest)
{
    const char *hostname = "127.0.0.1";
    const char *servname = "localhost";
    struct addrinfo hints;
    struct addrinfo *res = NULL;
    LONGS_EQUAL(0, getaddrinfo(hostname, servname, &hints, &res));
    CHECK_COMPARE(res, ==, test_ai);
    freeaddrinfo(res);
}