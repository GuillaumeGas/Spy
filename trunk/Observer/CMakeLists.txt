PROJECT(Observer CXX)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

ADD_DEFINITIONS(-std=c++0x -ggdb)

ADD_EXECUTABLE(out client.cc ../Spy/ScreenShot.cc)

TARGET_LINK_LIBRARIES(out -lboost_thread -lNet -lSDL -lSDL_gfx -lX11)
