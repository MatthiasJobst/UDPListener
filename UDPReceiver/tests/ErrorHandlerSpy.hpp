#ifndef ERRORHANDLERSPY_HPP
#define ERRORHANDLERSPY_HPP

#include "src/ErrorHandler.hpp"

class ErrorHandlerSpy: public ErrorHandler 
{
public:
    ErrorHandlerSpy(void);
    void addError(char const*, char const*);
    const char *get_area(void);
    const char *get_error(void);
};
#endif