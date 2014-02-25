#include "Serv_session.hh"
#include <iostream>
using namespace std;

Serv_session::Serv_session(int sock) : Thread<Serv_session>(&Serv_session::session, this) {
    m_sock = sock;
}

void Serv_session::session() {
    cout << "j'ecoute " << m_sock << endl; 
}

Serv_session::~Serv_session() {
    cout << " j'ecoute plus sur " << m_sock << endl;
    //quit(sock); pour plus tard
}
