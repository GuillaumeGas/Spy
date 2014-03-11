PROJECT(example CXX)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

ADD_DEFINITIONS(-std=c++0x -ggdb)

ADD_EXECUTABLE(server server.cc)

ADD_EXECUTABLE(client client.cc)


ADD_EXECUTABLE(udp_client udp_client.cc)


TARGET_LINK_LIBRARIES(server -lNet -lboost_thread)
TARGET_LINK_LIBRARIES(client -lNet -lboost_thread)
TARGET_LINK_LIBRARIES(udp_client -lboost_thread -lNet)
