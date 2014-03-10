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
	ss >> port;
	change_write_port(port);
	cout << "[SYS] -> Are You Here ??" << endl;
	(*proto)["YES"]("localhost 8888");
    }

};


int main( int argc, char ** argv ) {
    Client_UDP < controller::spy_session > client ( argc, argv );
    client._session().start();
    client.join();
}
