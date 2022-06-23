#include "CppUTest/TestHarness.h"
#include  "src/UDPServerInfo.hpp"
#include "ErrorHandlerSpy.hpp"

extern "C"
{
   #include "src/SocketHelper.h"
   #include "NetworkSpy.h"
}

TEST_GROUP(ServerInfoTestGroup)
{
    UDPServerInfo *serverInfo;
    struct addrinfo hints, 
        storage,
        *spy_ai;
    ErrorHandlerSpy *error_handler;
    struct sockaddr ai_addr;

    void setup()
    {
        set_addrinfo_null(&hints);
        spy_ai = &storage;
        spy_ai->ai_addr = &ai_addr;
        spy_ai->ai_next = NULL;
        NetworkSpy_Create(&spy_ai);
        serverInfo = new UDPServerInfo(&hints);
        error_handler = new ErrorHandlerSpy();
        serverInfo->set_error_handler(error_handler);
    }

    void teardown()
    {
        delete serverInfo;
        delete error_handler;
    }
};

TEST(ServerInfoTestGroup, InitTest)
{
    ErrorHandler handler;
    serverInfo->set_error_handler(&handler);
}

TEST(ServerInfoTestGroup, GetServerInfoNullTest)
{
    POINTERS_EQUAL(nullptr, serverInfo->getServerInfo());
}

TEST(ServerInfoTestGroup, validInfoGottenForPortTest)
{
    const char *port = "1224";
    NetworkSpy_Set_Pass();
    CHECK(serverInfo->validInfoGottenForPort(port));
    LONGS_EQUAL(0, NetworkSpy_get_error());
    POINTERS_EQUAL(nullptr, error_handler->get_area());
    POINTERS_EQUAL(&storage, serverInfo->getServerInfo());
}