#include "controller.hh"
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


string load_rep () {
    ifstream file ( "rep" );
    string rep;
    file >> rep;
    return rep;
}


void loop_create(int salle, int write, int read) {
    stringstream ss;
    ss << "info" << salle << "-01";
    Client_UDP < controller::controller_session > client(ss.str(), read, write);
    client._session().set_port ( read );
    system("hostname > rep ");
    client._session().set_ip( load_rep() );
    client._session().start();
    for ( int i = 1 ; i < 30 ; i++) {
	ss.str("");
	ss << "info" << salle << "-";
	if ( i < 10 ) {
	    ss << "0";
	} 
	ss << i;
	client._session().change_write_port( write , ss.str() );
	client._session().send();
	/*	if ( client._session().received() ) {
	    send_to_master(client._session().info() );
	} else {
	    continue;
	    }*/
    }
    client._session().change_write_port( read, "info23-21" );
    client.join();
}


void home_test(int argc, char ** argv) {
    Client_UDP < controller::controller_session > client (argc, argv);
    client._session().set_port( 9999 );
    client._session().set_ip( "localhost" );
    client._session().start();
    client.join();
}



int main(int argc, char ** argv) {
    int salle;
    cout << "Salle :";
    cin >> salle;
    loop_create(salle, 8888, 9999);
    //home_test(argc, argv);
}
