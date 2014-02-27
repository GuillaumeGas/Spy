PROJECT(Net)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
ADD_DEFINITIONS(-std=c++0x -ggdb)
file(
  GLOB_RECURSE
  sources_file 
  ./*.cc
)

SET(LIBRARY_OUTPUT_PATH /usr/local/lib/)
ADD_LIBRARY(Net SHARED ${sources_file})

TARGET_LINK_LIBRARIES(Net -lboost_thread -lboost_system)

