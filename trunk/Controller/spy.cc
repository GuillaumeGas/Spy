#include "spy.hh"
#include <sstream>

using namespace std;


namespace controller {


    spy_session::spy_session ( int & write, int & read, string & ip ) 
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
	cout << "[SYS] -> Are You Here ??" << endl;
	ss.str("");
	ss << m_ip << " " << m_port;
	(*proto)["YES"](ss.str());
    }


    void spy_session::set_ip ( string ip ) {
	m_ip = ip;
    }

    void spy_session::set_port ( int port ) {
	m_port = port;
    }

};


int main( int argc, char ** argv ) {
    Client_UDP < controller::spy_session > client ( argc, argv );
    client._session().set_port( 8888 );
    client._session().set_ip( "localhost" );
    client._session().start();
    client.join();
}
