#ifndef _UDP_MESSAGE
#define _UDP_MESSAGE


#include <iostream>
#include <boost/signals2.hpp>
#include "UDP_protocol.hh"

using boost::signals2::signal;


class UDP_Message {
public:
    UDP_Message ( std::string nom, std::string format, UDP_Protocol * s);
    bool operator==(std::string);
    void operator()(std::string);

    std::string get_format();
    std::string get_name();


    signal <void(std::string) > sig_recv;
    signal <void(UDP_Message &, std::string) > sig_send;

private:
    std::string m_name;
    std::string m_format;

};


#endif
