#include "UDPReceiverError.hpp"
#include <cstdio>

void UDPReceiverError::addError(char const *area, char const *error)
{
    fprintf(stderr, "%s: %s\n", area, error);
}