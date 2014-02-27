#ifndef _PROTOCOL
#define _PROTOCOL

#include <iostream>
#include <map>

#include "Stream_net.hh"

class Message;

class Protocol {
public:

    Protocol(int socket);
    void send_msg(Message &s, std::string);
    std::string wait(Message &s);

    std::map< std::string, Message*> message;
    Stream_net my_stream;
    int m_sock;


};




#endif
