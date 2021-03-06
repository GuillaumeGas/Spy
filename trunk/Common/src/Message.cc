#include "../include/Message.hh"
using namespace std;

Message::Message(string name, string format, Protocol * s) {
    m_name = name;
    m_format = format;
    sig_send.connect(boost::bind(&Protocol::send_msg, s, _1, _2));
    p_recv.connect ( boost::bind ( &Protocol::wait_msg , s, _1));
}

bool Message::operator==(string name) {
    return m_name == name;
}

void Message::operator()(string content) {
    sig_send(*this, content);
}

string Message::get_format() {
    return m_format;
}

string Message::get_name() {
    return m_name;
}


void Message::recv ( ) {
    p_recv ( *this );
}
