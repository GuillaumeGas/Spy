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
	cout << "[INFO] -> new Spy at " << addr << ":" << port << " name " << name << endl;
	m.lock();
	spy_connected[name] = pair<string, int>(addr, port);
	m.unlock();
	(*proto)["OK"]("");
    }


    void session_on_server::do_dspy( string msg ) {
	stringstream ss(msg);
	string name;
	ss >> name;
	m.lock();
	if ( auto it = spy_connected.find(name) != spy_connected.end() ) {
	    (*proto)["OK"]("");
	    cout << "[INFO] -> Spy name " << name << " has deco " << endl;
	} else {
	    (*proto)["ERR"]("");
	    cout << "[ERROR] -> unknown Spy try to deco " << endl;
	}
	m.unlock();
    }


    void session_on_server::do_control(string msg) {
	cout << "[INFO] -> request from Controller" << endl;
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
	cout << "[INFO] -> request from Observer" << endl;
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
