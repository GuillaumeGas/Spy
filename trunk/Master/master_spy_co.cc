#include "client.hh"
#include <sstream>

using namespace std;


namespace master {


    master_spy_co::master_spy_co ( int socket ) : Client_session( socket ) {
	proto = new master_proto(socket);
	(*proto)["OK"].sig_recv.connect(boost::bind(&master_spy_co::do_ok, this, _1));
	(*proto)["ERR"].sig_recv.connect(boost::bind(&master_spy_co::do_err, this, _1));
	begin.connect(boost::bind(&master_spy_co::do_begin, this));
	m_isset = false;
    }

    void master_spy_co::do_begin() {
	while ( !m_isset ) {}
	stringstream ss;
	ss << m_name << " " << m_addr << " " << m_port;
	(*proto)["SPY"](ss.str());
    }


    void master_spy_co::do_ok ( string msg ) {
	cout << "[SYS] -> OK " << endl;
	m_stop = true;
    }

    void master_spy_co::do_err ( string msg ) {
	cout << "[SYS] -> ERR " << endl;
	m_stop = true;
    }


    string & master_spy_co::name() {
	return m_name;
    }
    
    string & master_spy_co::addr() {
	return m_addr;
    }

    int & master_spy_co::port() {
	return m_port;
    }

    bool & master_spy_co::isset() {
	return m_isset;
    }


};
