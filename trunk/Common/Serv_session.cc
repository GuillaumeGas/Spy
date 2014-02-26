#include "Serv_session.hh"
#include <iostream>
#include "Stream_net.hh"
using namespace std;

Serv_session::Serv_session(int sock) : Thread<Serv_session>(&Serv_session::session, this) {
    m_sock = sock;
    stop = false;
}


void Serv_session::loop_recv() {
    cout << "ici" << endl;
    while ( not stop ) {
	Stream_net m(m_sock);
	string msg;
	m >> msg;
	cout << msg << endl;
    }
}

void Serv_session::session() {
    boost::thread(boost::bind(&Serv_session::loop_recv, this));
    Stream_net m(m_sock);
    m << "1s5i" << "jean_claude" <<  10 << 4 << 6 << 7 << 5 ;
    m << "1i1s" << 45 << "machin";
    int a;
    cin >> a;
    stop = true;
}

Serv_session::~Serv_session() {
    cout << " j'ecoute plus sur " << m_sock << endl;
    //quit(sock); pour plus tard
}
