PROJECT(example CXX)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

ADD_DEFINITIONS(-std=c++0x -ggdb)

ADD_EXECUTABLE(server server.cc ../Common/Serv_session.cc ../Common/Stream_net.cc ../Common/Message.cc ../Common/protocol.cc)

ADD_EXECUTABLE(client client.cc ../Common/Client_session.cc ../Common/Stream_net.cc ../Common/Message.cc ../Common/protocol.cc)


ADD_EXECUTABLE(udp_client udp_client.cc ../Common/Client_UDPSession.cc)


TARGET_LINK_LIBRARIES(server -Wl,--copy-dt-needed-entries -lboost_thread)
TARGET_LINK_LIBRARIES(client -Wl,--copy-dt-needed-entries -lboost_thread)
TARGET_LINK_LIBRARIES(udp_client -lboost_thread -lNet)
