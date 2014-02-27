#ifndef _MESSAGE
#define _MESSAGE

#include <iostream>
#include "Stream_net.hh"
#include "Serv_session.hh"
#include <boost/signals2.hpp>

using boost::signals2::signal;


class Message {
public:

    Message( std::string nom, std::string format, Serv_session * s);
    bool operator==(std::string);
    void operator()(std::string);

    std::string get_format();
    std::string get_name();

    signal<void(std::string)> sig_recv;
    signal<void(Message&, std::string)> sig_send;
    
private:    
    std::string m_name;
    std::string m_format;
};


#endif
