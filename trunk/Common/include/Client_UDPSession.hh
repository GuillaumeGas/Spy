#ifndef _CLIE_UDPSESSION
#define _CLIE_UDPSESSION


#include <map>
#include <iostream>
#include <boost/signals2.hpp>
#include "UDP_protocol.hh"
#include "Thread.hh"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>


using boost::signals2::signal;

class UDP_Message;

class Client_UDPSession : public Thread < Client_UDPSession > {

public:

    Client_UDPSession ( int & , int & , std::string & );
    void loop_recv();
    void change_write_port( int , std::string );

    UDP_Protocol * proto;

protected:

    signal <void()> sig_begin;
    signal <void()> sig_end;

    sockaddr_in m_sin;
    bool m_stop;

};





#endif

