#include <iostream>
#include "server.hh"
#include <sstream>

using namespace std;




namespace master {

    map <std::string, pair<std::string, int> > spy_connected;

    session_on_server::session_on_server ( int socket ) : Serv_session(socket) {
	proto = new master_proto(socket);
	(*proto)["SPY"].sig_recv.connect(boost::bind(&session_on_server::do_spy, this, _1));
	(*proto)["DSPY"].sig_recv.connect(boost::bind(&session_on_server::do_dspy, this, _1));
	(*proto)["CONTROL"].sig_recv.connect(boost::bind(&session_on_server::do_control, this, _1));
	(*proto)["OBSERVE"].sig_recv.connect(boost::bind(&session_on_server::do_observe, this, _1));
    }


    void session_on_server::do_spy(string msg) {
	stringstream ss(msg);
	int port;
	string addr, name;
	ss >> name >> addr >> port;

	m.lock();
	bool exist = false;
	for ( auto it : spy_connected ) {
	    if ( it.first == name ) {
		exist = true;
	    } else if ( it.second.first == addr && it.second.second == port ) {
		exist = true;
	    }
	}
	m.unlock();
	if ( !exist ) {
	    spy_connected[name] = pair<string, int>(addr, port);
	    (*proto)["OK"]("");
	    cout << "[INFO] -> Nouveau Spy a " << addr << ":" << port << " nomme " << name << endl;
	} else {
	    (*proto)["ERR"]("");
	    cout << "[ERROR] -> Spy " << name << " exist deja mais a tentant de se connecter" << endl;
	}
    }


    void session_on_server::do_dspy( string msg ) {
	stringstream ss(msg);
	string name;
	ss >> name;
	m.lock();
	if ( auto it = spy_connected.find(name) != spy_connected.end() ) {
	    (*proto)["OK"]("");
	    cout << "[INFO] -> Spy nomme " << name << " s'est deco " << endl;
	} else {
	    (*proto)["ERR"]("");
	    cout << "[ERROR] -> Spy inconnu tente de se deconnecte " << endl;
	}
	m.unlock();
    }


    void session_on_server::do_control(string msg) {
	cout << "[INFO] -> requete d'un Controller" << endl;
	m.lock();
	for ( auto it : spy_connected ) {
	    stringstream ss;
	    ss << it.first << " " << it.second.first << " " << it.second.second;    
	    (*proto)["SPY"](ss.str());
	}
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
}
