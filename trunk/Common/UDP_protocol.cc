#include "UDP_protocol.hh"
#include "UDP_Message.hh"


UDP_Protocol::UDP_Protocol ( int & port1, int & port2 , std::string & ip ) {
    m_sendsocket = socket ( AF_INET, SOCK_DGRAM, 0 );
    m_sendsin.sin_addr.s_addr = htonl(INADDR_ANY);
    m_sendsin.sin_family = AF_INET;
    m_sendsin.sin_port = htons(port2);
    hostent * hostinfo = NULL;
    hostinfo = gethostbyname(ip.c_str());
    m_sendsin.sin_addr = *(in_addr*)hostinfo->h_addr;
    
    m_sock = socket( AF_INET, SOCK_DGRAM, 0);
    m_sin.sin_addr.s_addr = htonl(INADDR_ANY);
    m_sin.sin_family = AF_INET;
    m_sin.sin_port = htons(port1);

    if ( bind(m_sock, (sockaddr*)&m_sin, sizeof(m_sin)) == -1 ) {
	std::cout << "erreur de bind changer de port" << std::endl;
	throw m_port;
    }
}
    
using namespace std;

void UDP_Protocol::send_msg( UDP_Message & m, string msg ) {
    cout << "ici" << endl;
    sendto (m_sendsocket, m.get_name().c_str(), m.get_name().length() + 1, 0, (sockaddr *)&m_sendsin, sizeof(m_sendsin));
}


string UDP_Protocol::wait( UDP_Message & m ) {
    return "";
}

void UDP_Protocol::waitmsg( string & msg ) {
    char buffer[255];
    sockaddr * sin = new sockaddr;
    socklen_t sizesin = sizeof(sin);
    int n = recvfrom(m_sock, buffer, 254, 0, sin, &sizesin);
    buffer[n] = 0;
    msg = buffer;
}


UDP_Message & UDP_Protocol::operator[]( string key ) {
    return *message[key];
}
