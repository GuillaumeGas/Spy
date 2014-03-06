#ifndef _UDP_PROTOCOL
#define _UDP_PROTOCOL


#include <iostream>
#include <map>


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

    UDP_Protocol ( sockaddr_in sin );
    void send_msg( UDP_Message &, std::string );
    std::string wait( UDP_Message & );
    UDP_Message & operator[]( std::string key );

    std::map < std::string, UDP_Message*> message;
    sockaddr_in m_sin;

};




#endif
