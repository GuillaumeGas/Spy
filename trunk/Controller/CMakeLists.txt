PROJECT(example CXX)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

ADD_DEFINITIONS(-std=c++0x -ggdb)

ADD_EXECUTABLE(client client.cc ../Master/master_cont.cc)



TARGET_LINK_LIBRARIES(client  -lNet -lboost_thread)

