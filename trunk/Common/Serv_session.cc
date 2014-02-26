#include "Serv_session.hh"
#include <iostream>
#include "Stream_net.hh"
using namespace std;

Serv_session::Serv_session(int sock) : Thread<Serv_session>(&Serv_session::session, this) {
    m_sock = sock;
}

void Serv_session::session() {
    Stream_net m(m_sock);
    std::string s("salut1s");
    m << "1s" << "jean-claude" << "1s" << "salut";
}

Serv_session::~Serv_session() {
    cout << " j'ecoute plus sur " << m_sock << endl;
    //quit(sock); pour plus tard
}
