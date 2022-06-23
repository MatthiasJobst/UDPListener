#ifndef WITHERRORHANDLER_HPP
#define WITHERRORHANDLER_HPP

#include "ErrorHandler.hpp"

class WithErrorHandler
{
public:
    virtual void set_error_handler(ErrorHandler *) = 0;
};

#endif