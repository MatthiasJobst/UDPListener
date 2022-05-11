cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)

project(UDPReceiver)

set(UDPReceiver_version_major 1)
set(UDPReceiver_version_minor 0)

include_directories(${PROJECT_SOURCE_DIR} /usr/local/opt/cpputest/include/)

add_library(CppUTest STATIC IMPORTED)
set_property(TARGET CppUTest PROPERTY IMPORTED_LOCATION "/usr/local/opt/cpputest/lib/libCppUTest.a")
add_library(CppUTestExt STATIC IMPORTED)
set_property(TARGET CppUTestExt PROPERTY IMPORTED_LOCATION "/usr/local/opt/cpputest/lib/libCppUTestExt.a")

add_library(UDPReceiverLib src/UDPReceiver.cpp)
add_executable(UDPReceiverTest tests/AllTests.cpp tests/BasicFunctionTests.cpp)
target_link_libraries(UDPReceiverTest UDPReceiverLib CppUTest CppUTestExt)