#include "spy.hh"
#include <sstream>

using namespace std;


namespace controller {


    spy_session::spy_session ( int  write, int read, string ip ) 
	: Client_UDPSession( write, read, ip ) {
	proto = new cont_proto( write, read, ip );
	(*proto)["HERE?"].sig_recv.connect( boost::bind( &spy_session::do_HERE, this, _1));
    }

    void spy_session::do_HERE( string msg ) {
	stringstream ss(msg);
	int port;
	string addr;
	ss >> addr >> port;
	change_write_port(port, addr);
	cout << " send to "<< addr << ":" << port << endl;
	cout << "[SYS] -> Are You Here ??" << endl;
	ss.str("");
	ss << m_name << " " << m_ip << " " << m_port;
	(*proto)["YES"](ss.str());
	change_write_port( m_port, m_ip);
    }


    void spy_session::set_ip ( string ip ) {
	m_ip = ip;
    }

    void spy_session::set_port ( int port ) {
	m_port = port;
    }

    void spy_session::set_name ( string name ) {
	m_name = name;
    }


};

