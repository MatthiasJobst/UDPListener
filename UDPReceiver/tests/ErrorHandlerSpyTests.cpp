#include "CppUTest/TestHarness.h"
#include "ErrorHandlerSpy.hpp"

TEST_GROUP(ErrorHandlerSpyTestGroup)
{
    ErrorHandlerSpy *error_handler;

    void setup()
    {
        error_handler = new ErrorHandlerSpy();
    }

    void teardown()
    {
        delete error_handler;
    }
};

TEST(ErrorHandlerSpyTestGroup, InitTest)
{
    POINTERS_EQUAL(nullptr, error_handler->get_area());
    POINTERS_EQUAL(nullptr, error_handler->get_error());
}

TEST(ErrorHandlerSpyTestGroup, FunctionTest)
{
    error_handler->addError("location", "error");
    STRCMP_EQUAL("location", error_handler->get_area());
    STRCMP_EQUAL("error", error_handler->get_error());
}