cmake_minimum_required(VERSION 3.1)

project(UDPReceiver)

set(UDPReceiver_version_major 1)
set(UDPReceiver_version_minor 0)

include_directories(${PROJECT_SOURCE_DIR})
add_library(UDPReceiverLib src/UDPReceiver.cpp)
add_executable(UDPReceiverTest tests/AllTests.cpp tests/BasicFunctionTests.cpp)
target_link_libraries(UDPReceiverTest UDPReceiverLib)