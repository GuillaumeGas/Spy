#ifndef _UDP_PROTOCOL
#define _UDP_PROTOCOL


#include <iostream>
#include <map>
#include <sstream>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>


class UDP_Message;

class UDP_Protocol {

public:

    UDP_Protocol ( int & port , int & ,std::string &sock);
    void send_msg( UDP_Message &, std::string );
    std::string wait( UDP_Message & );
    void waitmsg( std::string & s);
    UDP_Message & operator[]( std::string key );
    void change_write_port(int);



    std::stringstream m_tmp;
    std::map < std::string, UDP_Message*> message;
    sockaddr_in m_sin, m_sendsin;
    int m_sock, m_sendsocket;
    int m_port;
    std::string m_ip;
};




#endif
