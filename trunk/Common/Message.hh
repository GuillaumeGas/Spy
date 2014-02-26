#ifndef _MESSAGE
#define _MESSAGE

#include <iostream>
#include "Stream_net.hh"
#include <boost/signals2.hpp>

using boost::signals2::signal;


class Message {
public:


    Message(std::string name, std::string content) {
	m_name = name;
	m_content = content;

    }
    

    void operator==(std::string name) {
	return m_name == name;
    }
    
    
    void operator()(Stream_net & s) {
	sig_send(s, m_name+m_content);
    }


    signal<void(Stream_net&, std::string )> sig_send;
    signal<void()> sig_recv;

private:
    std::string m_name;
    std::string m_content;
};



#endif
