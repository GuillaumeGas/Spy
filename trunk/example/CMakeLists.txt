PROJECT(example CXX)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

ADD_DEFINITIONS(-std=c++0x -ggdb)

ADD_EXECUTABLE(out main.cc)



TARGET_LINK_LIBRARIES(out -Wl,--copy-dt-needed-entries -lboost_thread)

