#include "client.hh"
#include <sstream>
using namespace std;


namespace master {


    master_cont::master_cont( int socket ) :Client_session ( socket ) {
	proto = new master_proto( socket );
	(*proto)["OK"].sig_recv.connect(boost::bind(&master_cont::do_ok, this, _1));
	(*proto)["ERR"].sig_recv.connect(boost::bind(&master_cont::do_err, this, _1));
    }


    void master_cont::do_ok( string msg ) {
	cout << "[SYS] -> OK " << endl;
	m_stop = true;
    }
    
    void master_cont::do_err( string msg ) {
	cout << "[SYS] -> ERR " << endl;
	m_stop = true;
    }
    
    void master_cont::send_map ( stringstream & ss ) {
	(*proto)["MAP_SPY"](ss.str());
    }

};
