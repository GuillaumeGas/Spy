PROJECT(Spy CXX)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

ADD_DEFINITIONS(-std=c++0x -ggdb)

ADD_EXECUTABLE(Spy server.cc Process.cc ScreenShot.cc ../Controller/spy.cc)

TARGET_LINK_LIBRARIES(Spy -lboost_thread -lNet -lSDL -lSDL_gfx -lX11)
