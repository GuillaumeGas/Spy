#ifndef _PROTOCOL
#define _PROTOCOL

#include <iostream>
#include <map>

#include "Stream_net.hh"
#include "Annotation.hh"
#include "Anc_Message.hh"

class Message;
class Img_Message;

class Protocol {
public:

    Protocol(int socket);
    void send_msg(Message &s, std::string);
    void send_img( Img_Message &, std::string, int h, int l );
    std::string wait(Message &s);
    Message & operator[](std::string key);
    Img_Message & operator()( std::string );

    void wait_msg ( Message & m );
    void wait_img ( Img_Message & m );

    void unactive_annotation( Annotation::Flags );
    void unactive_annotation( );

    void reactive_annotation( Annotation::Flags );
    void reactive_annotation( );


    std::map< std::string, Message*> message;
    std::map< std::string, Img_Message*> imessage;
    Stream_net my_stream;
    int m_sock;
    Annotation a;

};




#endif
