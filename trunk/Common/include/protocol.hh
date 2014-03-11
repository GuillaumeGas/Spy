#ifndef _PROTOCOL
#define _PROTOCOL

#include <iostream>
#include <map>

#include "Stream_net.hh"
#include "Annotation.hh"

class Message;

class Protocol {
public:

    Protocol(int socket);
    void send_msg(Message &s, std::string);
    std::string wait(Message &s);
    Message & operator[](std::string key);

    void unactive_annotation( Annotation::Flags );
    void unactive_annotation( );

    void reactive_annotation( Annotation::Flags );
    void reactive_annotation( );


    std::map< std::string, Message*> message;
    Stream_net my_stream;
    int m_sock;
    Annotation a;

};




#endif
