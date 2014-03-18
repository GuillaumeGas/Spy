PROJECT(SPY CXX)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
ADD_DEFINITIONS(-std=c++0x -ggdb)
FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})




file(
  GLOB_RECURSE
  Common_sources_file 
  Common/src/*.cc
)

SET(LIBRARY_OUTPUT_PATH ~/lib/)
ADD_LIBRARY(Net SHARED ${Common_sources_file})

TARGET_LINK_LIBRARIES(Net -lboost_thread -lboost_system)


file(
  GLOB_RECURSE
  Obs_header_files
  Observer/*.hh
)

QT4_WRAP_CPP(MOCSrcs ${Obs_header_files})


file(
  GLOB_RECURSE
  Obs_source_files
  Observer/*.cc
)
ADD_EXECUTABLE(observer ${Obs_source_files} Spy/ScreenShot.cc Spy/Process.cc ${MOCSrcs} Master/master_obse.cc)


TARGET_LINK_LIBRARIES(observer -lboost_thread -lNet -lSDL -lSDL_gfx -lX11 ${QT_LIBRARIES})


ADD_EXECUTABLE(controller Controller/controller.cc Master/master_cont.cc Controller/Sniffer.cc)
TARGET_LINK_LIBRARIES(controller -lboost_thread -lNet)


ADD_EXECUTABLE(spy Spy/server.cc Spy/Process.cc Spy/ScreenShot.cc Controller/spy.cc)
TARGET_LINK_LIBRARIES(spy -lboost_thread -lNet -lSDL -lSDL_gfx -lX11)

ADD_EXECUTABLE(master Master/server.cc)
TARGET_LINK_LIBRARIES(master -lNet -lboost_thread) 


