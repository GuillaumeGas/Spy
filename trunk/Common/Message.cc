#include "Message.hh"
using namespace std;

Message::Message(string name, string format, Session * s) {
    m_name = name;
    m_format = format;
    sig_send.connect(boost::bind(&Serv_session::send_msg, s, _1, _2));
    
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
