#include "client.hh"
#include <sstream>

using namespace std;


namespace master {
   
    master_spy_deco::master_spy_deco ( int socket ) : Client_session ( socket ) {
	proto = new master_proto(socket);
	(*proto)["OK"].sig_recv.connect(boost::bind(&master_spy_deco::do_ok, this, _1));
	(*proto)["ERR"].sig_recv.connect(boost::bind(&master_spy_deco::do_err, this, _1));
	begin.connect(boost::bind(&master_spy_deco::do_begin, this));
    }

    void master_spy_deco::do_begin() {
	(*proto)["DSPY"]("norbert");
    }

    void master_spy_deco::do_ok( string msg ) {
	cout << "[SYS] -> OK " << endl;
	m_stop = true;
    }

    void master_spy_deco::do_err( string msg ) {
	cout << "[SYS] -> ERR " << endl;
	m_stop = true;
    }


};
