#include "ErrorHandlerSpy.hpp"

const char *area_spy = nullptr;
const char *error_spy = nullptr;

void ErrorHandlerSpy::addError(const char *source, const char *error)
{
    area_spy = source;
    error_spy = error;
}

const char *ErrorHandlerSpy::get_area()
{
    return area_spy;
}

const char *ErrorHandlerSpy::get_error()
{
    return error_spy;
}