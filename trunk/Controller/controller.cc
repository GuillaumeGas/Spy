#include "controller.hh"
#include <sstream>

using namespace std;

namespace controller {


    controller_session::controller_session ( int & write, int & read, string & ip )
	: Client_UDPSession ( write, read, ip ) {
	proto = new cont_proto ( write, read, ip );
	(*proto)["YES"].sig_recv.connect( boost::bind ( &controller_session::do_YES, this, _1));
	sig_begin.connect(boost::bind( &controller_session::on_begin, this));
    }

    void controller_session::on_begin() {
	stringstream ss;
	ss << m_ip << " " << m_port;
	(*proto)["HERE?"](ss.str());
    }

    void controller_session::set_ip( string ip ) {
	m_ip = ip;
    }

    void controller_session::set_port ( int port )  {
	m_port = port;
    }


    void controller_session::do_YES ( string msg ) {
	stringstream ss(msg);
	int port;
	string addr;
	ss >> addr >> port;
	cout << "[SYS] -> Yes " << addr << ":" << port << endl;
    }
    
    bool controller_session::received() {
	return m_recv;
    }
    
    string controller_session::info() {
	return m_info;
    }
    
};



void send_to_master ( string s ) {
}

void loop_create(int salle, int write, int read) {
    stringstream ss;

    for ( int i = 0 ; i < 30 ; i++) {
	ss << "info" << salle;
	if ( i < 10 ) {
	    ss << "0";
	} 
	ss << i;
	Client_UDP < controller::controller_session > client(ss.str(), write, read);
	client._session().start();
	sleep(1);
	if ( client._session().received() ) {
	    send_to_master(client._session().info() );
	} else {
	    continue;
	}
    }
}


void home_test(int argc, char ** argv) {
    Client_UDP < controller::controller_session > client (argc, argv);
    client._session().set_port( 9999 );
    client._session().set_ip( "localhost" );
    client._session().start();
    client.join();
}



int main(int argc, char ** argv) {
    //loop_create(23, 8000, 9000); testable uniquement a l'iut
    home_test(argc, argv);
}
