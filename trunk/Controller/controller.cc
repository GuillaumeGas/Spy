#include "controller.hh"
#include "../Master/client.hh"
#include "Sniffer.hh"
#include <sstream>
#include <fstream>

using namespace std;

namespace controller {


    controller_session::controller_session ( int & write, int & read, string & ip )
	: Client_UDPSession ( write, read, ip ) {
	proto = new cont_proto ( write, read, ip );
	(*proto)["YES"].sig_recv.connect( boost::bind ( &controller_session::do_YES, this, _1));
	sig_begin.connect(boost::bind( &controller_session::on_begin, this));
    }

    void controller_session::on_begin() {
    }


    void controller_session::send() {
	stringstream ss;
	ss << m_ip << " " << m_port;
	(*proto)["HERE?"](ss.str());
    }


    void controller_session::set_ip( string ip ) {
	cout << ip << endl;
	m_ip = ip;
    }

    void controller_session::set_port ( int port )  {
	m_port = port;
    }


    void controller_session::do_YES ( string msg ) {
	stringstream ss(msg);
	ss >> name >> ip >> port;
	cout << "[SYS] -> Yes " << name << " " << ip << ":" << port << endl;
	m_recv = true;
    }
    
    bool controller_session::received() {
	return m_recv;
    }
    
    string controller_session::info() {
	return m_info;
    }


    pair < string , pair < string, int > > controller_session::recv() {
	pair < string , pair < string, int > > p;
	p.first = name;
	p.second.first = ip;
	p.second.second = port;
	return p;
    }
    

    void controller_session::reset() {
	m_recv = false;
    }

};





int main(int argc, char ** argv) {
    int salle;
    cout << "Salle :";
    cin >> salle;
    controller::Sniffer s ( "localhost", 4444, 9999, 8888, salle );
    s.launch();
    s.join();
}
