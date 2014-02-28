#include "client.hh"
#include <sstream>

using namespace std;

namespace master {

    master_obse::master_obse ( int socket ) : Client_session( socket ) {
	proto = new master_proto(socket);
	(*proto)["OK"].sig_recv.connect(boost::bind(&master_obse::do_ok, this, _1));
	(*proto)["ERR"].sig_recv.connect(boost::bind(&master_obse::do_err, this, _1));
	(*proto)["SPY"].sig_recv.connect(boost::bind(&master_obse::do_spy, this, _1));
	begin.connect(boost::bind(&master_obse::do_begin, this));
    }


    void master_obse::do_begin() {
	(*proto)["OBSERVE"]("");
    }
    
    void master_obse::do_ok( string msg ) {
	cout << "[SYS] -> OK " << endl;
	m_stop = true;
    }

    void master_obse::do_err( string msg ) {
	cout << "[SYS] -> ERR " << endl;
	m_stop = true;
    }

    void master_obse::do_spy( string msg ) {
	stringstream ss(msg);
	int port;
	string name, addr;
	ss >> name >> addr >> port;
	spy[name] = pair<string, int>(addr, port);
    }

    void master_obse::aff_map() {
	for ( auto it : spy ) {
	    cout << it.first << " " << it.second.first << ":" << it.second.second << endl;
	}
    }
};
