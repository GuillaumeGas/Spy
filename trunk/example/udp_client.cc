#include <iostream>
#include "udp_proto.hh"
#include "../Common/Client_UDP.hh"
#include "../Common/Client_UDPSession.hh"
#include "../Common/UDP_Message.hh"

using namespace std;


class session_on_client : public Client_UDPSession {

public:


    session_on_client ( int & port, int & port2, string & ip ) : Client_UDPSession ( port, port2, ip ) {
	proto = new udp_proto ( port,port2, ip );
	(*proto)["salut"].sig_recv.connect(boost::bind ( &session_on_client::salut, this , _1));
	(*proto)["bonjour"].sig_recv.connect(boost::bind(&session_on_client::bonjour, this, _1));
	(*proto)["salut"]("");
	
    }

    void salut(string msg) {
	cout << "SALUT" << endl;
	(*proto)["bonjour"]("salut");
    }

    void bonjour( string msg ) {
	cout << "Bonjour -> " << msg << endl;
    }


};


int main( int argc, char ** argv ) {
    Client_UDP < session_on_client > client(argc, argv);
    client._session().start();
    client.join();
}
