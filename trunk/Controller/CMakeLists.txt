PROJECT(example CXX)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

ADD_DEFINITIONS(-std=c++0x -ggdb)

ADD_EXECUTABLE(client client.cc ../Master/master_cont.cc)
ADD_EXECUTABLE(server server.cc  ../Master/master_spy_co.cc ../Master/master_spy_deco.cc)



TARGET_LINK_LIBRARIES(client  -lNet -lboost_thread)
TARGET_LINK_LIBRARIES(server  -lNet -lboost_thread)

