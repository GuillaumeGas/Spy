PROJECT(Controller CXX)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

ADD_DEFINITIONS(-std=c++0x -ggdb)

ADD_EXECUTABLE(controller controller.cc ../Common/Client_UDPSession.cc)
ADD_EXECUTABLE(spy spy.cc ../Common/Client_UDPSession.cc)

TARGET_LINK_LIBRARIES(controller -lboost_thread -lNet)
TARGET_LINK_LIBRARIES(spy -lboost_thread -lNet)
