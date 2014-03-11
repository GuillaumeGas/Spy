#ifndef _MESSAGE
#define _MESSAGE

#include <iostream>
#include "Stream_net.hh"
#include "Serv_session.hh"
#include <boost/signals2.hpp>

using boost::signals2::signal;

class Message : public Anc_Message {
public:

    Message( std::string nom, std::string format, Protocol * s);
    bool operator==(std::string);
    void operator()(std::string);

    std::string get_format();
    std::string get_name();

    void recv ( );


    signal<void(std::string)> sig_recv;
    signal<void(Message&, std::string)> sig_send;
    signal< void ( Message & ) > p_recv;
private:    
    std::string m_name;
    std::string m_format;
};


#endif
