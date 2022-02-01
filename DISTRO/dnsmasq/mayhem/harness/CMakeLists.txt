cmake_minimum_required(VERSION 3.16)
project(harness)

set(CMAKE_CXX_STANDARD 14)

add_library(harness SHARED harness.cpp State.cpp State.h UntrackedState.cpp
    UntrackedState.h FuzzPayloadReadyState.cpp FuzzPayloadReadyState.h
    FakeNetlinkReadyState.cpp FakeNetlinkReadyState.h
    FakeNetlinkGetAddrState.cpp FakeNetlinkGetAddrState.h
    FakeNetlinkDoneState.cpp FakeNetlinkDoneState.h
    FuzzPayloadDeliveredState.cpp FuzzPayloadDeliveredState.h)
target_link_libraries(harness dl)
