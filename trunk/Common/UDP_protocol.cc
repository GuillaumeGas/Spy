#include "UDP_protocol.hh"
#include "UDP_Message.hh"
using namespace std;

UDP_Protocol::UDP_Protocol ( sockaddr_in sin ) {
    m_sin = sin;
    m_sock = socket(AF_INET, SOCK_DGRAM, 0);
}


void UDP_Protocol::send_msg( UDP_Message & m, string msg ) {
    sendto (m_sock, m.get_name().c_str(), m.get_name().length() + 1, 0, (sockaddr *)&m_sin, sizeof(m_sin));
}


string UDP_Protocol::wait( UDP_Message & m ) {
    return "";
}

void UDP_Protocol::waitmsg( string & msg ) {
    char buffer[255];
    socklen_t size = sizeof(m_sin);
    int n = recvfrom(m_sock, buffer, sizeof buffer -1 , 0, (sockaddr*)&m_sin, &size);
    if ( n != 0) {
	msg = buffer;
    } else {
	msg = "";
    }
}


UDP_Message & UDP_Protocol::operator[]( string key ) {
    return *message[key];
}
