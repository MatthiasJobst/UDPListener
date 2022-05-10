/*
   From: https://cpputest.github.io
*/

#include "/usr/local/opt/cpputest/include/CppUTest/CommandLineTestRunner.h"

int main(int ac, char** av)
{
   return CommandLineTestRunner::RunAllTests(ac, av);
}