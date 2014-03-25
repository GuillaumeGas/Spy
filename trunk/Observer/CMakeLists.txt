PROJECT(Observer CXX)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})

file(
  GLOB_RECURSE
  header_files
  *.hh
)
QT4_WRAP_CPP(MOCSrcs ${header_files})

ADD_DEFINITIONS(-std=c++0x -ggdb)

file(
  GLOB_RECURSE
  source_files
  *.cc
)
ADD_EXECUTABLE(Observer ${source_files} ../Spy/ScreenShot.cc ../Spy/Process.cc ${MOCSrcs} ../Master/master_obse.cc)

ADD_EXECUTABLE(Test main2.cpp client.cc)



TARGET_LINK_LIBRARIES(Observer -lboost_thread -lNet -lSDL -lSDL_gfx -lX11 ${QT_LIBRARIES})


TARGET_LINK_LIBRARIES(Test -lboost_thread -lNet -lSDL -lSDL_gfx -lX11 ${QT_LIBRARIES})
