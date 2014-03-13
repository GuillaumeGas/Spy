PROJECT(chat CXX)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})

QT4_WRAP_CPP(MOCSrcs MainWindow.hh dialog.hh ListViewDelegate.h)

ADD_DEFINITIONS(-std=c++0x -ggdb)


ADD_EXECUTABLE(client client.cc ListViewDelegate.cpp ${MOCSrcs})
ADD_EXECUTABLE(server server.cc)
TARGET_LINK_LIBRARIES(client -Wl,--copy-dt-needed-entries -lnetez ${QT_LIBRARIES} -pthread)
TARGET_LINK_LIBRARIES(server -Wl,--copy-dt-needed-entries -lnetez)

