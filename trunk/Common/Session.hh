#ifndef _SESSION
#define _SESSION

#include <iostream>
#include <map>
#include "Stream_net.hh"

class Message;

class Session {
public:

    Session(int);
    void send_msg(Message &s, std::string);
    std::string wait(Message &s);
    
protected:
    
    int m_sock;
    Stream_net my_stream;
    std::map < std::string, Message* > message;
};


#endif
