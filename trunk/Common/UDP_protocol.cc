#include "UDP_protocol.hh"
#include "UDP_Message.hh"
using namespace std;

UDP_Protocol::UDP_Protocol ( sockaddr_in sin ) {
    m_sin = sin;
}


void UDP_Protocol::send_msg( UDP_Message & m, string msg ) {
}


string UDP_Protocol::wait( UDP_Message & m ) {
}

UDP_Message & UDP_Protocol::operator[]( string key ) {
    return *message[key];
}
