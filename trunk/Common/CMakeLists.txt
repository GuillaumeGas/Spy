PROJECT(Spy CXX)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

ADD_DEFINITIONS(-std=c++0x -ggdb)

ADD_EXECUTABLE(client cli_main.cc Client_session.cc Stream_net.cc protocol.cc Message.cc)

ADD_EXECUTABLE(server serv_main.cc Serv_session.cc Stream_net.cc protocol.cc Message.cc)

TARGET_LINK_LIBRARIES(client -lboost_thread -lboost_system)

TARGET_LINK_LIBRARIES(server -lboost_thread -lboost_system)
