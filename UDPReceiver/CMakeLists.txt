cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG  "-g")

project(UDPReceiver)

set(UDPReceiver_version_major 1)
set(UDPReceiver_version_minor 0)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

include_directories(${PROJECT_SOURCE_DIR} /usr/local/opt/cpputest/include/)

add_library(CppUTest STATIC IMPORTED)
set_property(TARGET CppUTest PROPERTY IMPORTED_LOCATION "/usr/local/opt/cpputest/lib/libCppUTest.a")
add_library(CppUTestExt STATIC IMPORTED)
set_property(TARGET CppUTestExt PROPERTY IMPORTED_LOCATION "/usr/local/opt/cpputest/lib/libCppUTestExt.a")

add_library(UDPReceiver STATIC
    ${PROJECT_SOURCE_DIR}/src/UDPReceiver.cpp
    ${PROJECT_SOURCE_DIR}/src/UDPReceiver.hpp
    ${PROJECT_SOURCE_DIR}/src/UDPReceiverError.cpp
    ${PROJECT_SOURCE_DIR}/src/UDPReceiverError.hpp
    ${PROJECT_SOURCE_DIR}/src/ErrorHandler.hpp
    ${PROJECT_SOURCE_DIR}/src/UDPServerInfo.hpp
    ${PROJECT_SOURCE_DIR}/src/UDPServerInfo.cpp
    ${PROJECT_SOURCE_DIR}/src/WithErrorHandler.hpp)
add_library(SocketHelper OBJECT
    ${PROJECT_SOURCE_DIR}/src/SocketHelper.c
    ${PROJECT_SOURCE_DIR}/src/SocketHelper.h)
add_library(NetworkSpy OBJECT
    ${PROJECT_SOURCE_DIR}/tests/NetworkSpy.c 
    ${PROJECT_SOURCE_DIR}/tests/NetworkSpy.h)
add_library(SocketSpy OBJECT
    ${PROJECT_SOURCE_DIR}/tests/SocketSpy.c 
    ${PROJECT_SOURCE_DIR}/tests/SocketSpy.h)
add_library(ErrorHandlerSpy OBJECT
    ${PROJECT_SOURCE_DIR}/tests/ErrorHandlerSpy.cpp 
    ${PROJECT_SOURCE_DIR}/tests/ErrorHandlerSpy.hpp
    ${PROJECT_SOURCE_DIR}/src/ErrorHandler.hpp)

add_executable(UDPReceiverTest
    ${PROJECT_SOURCE_DIR}/tests/AllTests.cpp
    ${PROJECT_SOURCE_DIR}/tests/BasicFunctionTests.cpp
    ${PROJECT_SOURCE_DIR}/tests/UDPServerInfoTests.cpp
    ${PROJECT_SOURCE_DIR}/tests/NetworkSpyTests.cpp
    ${PROJECT_SOURCE_DIR}/tests/SocketSpyTests.cpp
    ${PROJECT_SOURCE_DIR}/tests/ErrorHandlerSpyTests.cpp)

target_link_libraries(UDPReceiverTest
    UDPReceiver
    $<TARGET_OBJECTS:SocketHelper>
    $<TARGET_OBJECTS:NetworkSpy>
    $<TARGET_OBJECTS:SocketSpy>
    $<TARGET_OBJECTS:ErrorHandlerSpy>
    CppUTest
    CppUTestExt)    