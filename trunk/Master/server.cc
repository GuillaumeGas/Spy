#include <iostream>
#include "server.hh"
#include <sstream>

using namespace std;




namespace master {

    map <std::string, pair<std::string, int> > spy_connected;

    session_on_server::session_on_server ( int socket ) : Serv_session(socket) {
	proto = new master_proto(socket);
	(*proto)["OBSERVE"].sig_recv.connect(boost::bind(&session_on_server::do_observe, this, _1));

	(*proto)["MAP_SPY"].sig_recv.connect( boost::bind ( &session_on_server::do_control, this, _1) );

    }

    void session_on_server::affiche ( ) {
	system ( "clear" );
	for ( auto i : spy_map ) {
	    for ( auto it : i.second ) {
		cout << it.first << " " << it.second.first << ":" << it.second.second << endl;
	    }
	}
    }



    void session_on_server::do_control(string msg) {
	cout << "[INFO] -> requete d'un Controller" << endl;
	stringstream ss(msg);
	int size, port;
	string salle, name, ip;
	ss >> size >> salle;
	m.lock();
	spy_map[salle].clear();
	
	for ( int i = 0 ; i < size ; i++ ) {
	    ss >> name >> ip >> port;
	    cout << name << " " << ip << ":" << port << endl;
	    spy_map[salle][name] = pair<string, int>( ip , port );
	}
	affiche( );
	m.unlock();
	(*proto)["OK"]("");
    }

    void session_on_server::do_observe(string msg) {
	cout << "[INFO] -> requete d'un Observer" << endl;
	m.lock();
	for ( auto it : spy_connected ) {
	    stringstream ss;
	    ss << it.first << " " << it.second.first << " " << it.second.second;    
	    (*proto)["SPY"](ss.str());
	}	
	m.unlock();
	(*proto)["OK"]("");
    }

};


int main(int argc, char ** argv) {
    Server <master::session_on_server> serv(argc, argv);
    serv.start();
    serv.join();
}
