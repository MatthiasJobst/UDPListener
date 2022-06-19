#include "CppUTest/TestHarness.h"
#include  "src/UDPServerInfo.hpp"
extern "C"
{
   #include "src/SocketHelper.h"
}

TEST_GROUP(ServerInfoTestGroup)
{
    UDPServerInfo *serverInfo;
    struct addrinfo hints;

    void setup()
    {
        set_addrinfo_null(&hints);
        serverInfo = new UDPServerInfo(&hints);
    }

    void teardown()
    {
        delete serverInfo;
    }
};

TEST(ServerInfoTestGroup, InitTest)
{
    
}