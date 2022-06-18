#ifndef UDPReceiverError_hpp
#define UDPReceiverError_hpp

#include "ErrorHandler.hpp"

class UDPReceiverError: public ErrorHandler
{
public:
    void addError(char const*, char const*);
};
#endif