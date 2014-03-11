#include "client.hh"
#include <sstream>

using namespace std;

namespace master {

    master_obse::master_obse ( int socket ) : Client_session( socket ) {
	proto = new master_proto(socket);
	(*proto)["OK"].sig_recv.connect(boost::bind(&master_obse::do_ok, this, _1));
	(*proto)["ERR"].sig_recv.connect(boost::bind(&master_obse::do_err, this, _1));
	(*proto)["MAP_SPY"].sig_recv.connect( boost::bind ( &master_obse::do_map_spy, this, _1));
    }


    void master_obse::do_ok( string msg ) {
	cout << "[SYS] -> OK " << endl;
	m_stop = true;
    }

    void master_obse::do_err( string msg ) {
	cout << "[SYS] -> ERR " << endl;
	m_stop = true;
    }

    void master_obse::do_map_spy ( string msg ) {
	stringstream ss(msg);
	int size;
	ss >> size;
	for ( int i = 0 ; i < size ; i++) {
	    string name, ip;
	    int port;
	    ss >> name >> ip >> port;
	    spy_map[name] = pair < string, int >(ip, port);
	}
	m_recv = true;
    }

    bool master_obse::received() {
	return m_recv;
    }


    void master_obse::reset() {
	m_recv = false;
	spy_map.clear();
    }


    void master_obse::send(string salle) {
	(*proto)["OBSERVE"](salle);
    }

    map < string, pair < string, int > > & master_obse::get_map () {
	return spy_map;
    }
};
