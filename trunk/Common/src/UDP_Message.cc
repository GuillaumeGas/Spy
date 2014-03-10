#include "../include/UDP_Message.hh"
using namespace std;


UDP_Message::UDP_Message( string name, string format, UDP_Protocol * s ) {
    m_name = name;
    m_format = format;
    sig_send.connect( boost::bind( &UDP_Protocol::send_msg, s, _1, _2));
}


bool UDP_Message::operator==( string name ) {
    return m_name == name;
}

void UDP_Message::operator()( string msg ) {
    sig_send(*this, msg);
}

string UDP_Message::get_format() {
    return m_format;
}

string UDP_Message::get_name() {
    return m_name;
}
