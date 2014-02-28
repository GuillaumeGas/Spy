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





    master_cont::master_cont( int socket ) :Client_session ( socket ) {
	proto = new master_proto( socket );
	(*proto)["OK"].sig_recv.connect(boost::bind(&master_cont::do_ok, this, _1));
	(*proto)["ERR"].sig_recv.connect(boost::bind(&master_cont::do_err, this, _1));
	(*proto)["SPY"].sig_recv.connect(boost::bind(&master_cont::do_spy, this, _1));
	begin.connect(boost::bind(&master_cont::do_begin, this));
    }


    void master_cont::do_begin() {
	(*proto)["CONTROL"]("");
    }

    void master_cont::do_ok( string msg ) {
	cout << "[SYS] -> OK " << endl;
	aff_map();
	m_stop = true;
    }
    
    void master_cont::do_err( string msg ) {
	cout << "[SYS] -> ERR " << endl;
	m_stop = true;
    }

    void master_cont::do_spy( string msg ) {
	stringstream ss(msg);
	int port;
	string name, addr;
	ss >> name >> addr >> port;
	spy[name] = pair<string, int>(addr, port);	
    }


    void master_cont::aff_map() {
	for ( auto it : spy ) {
	    cout << it.first << " " << it.second.first << ":" << it.second.second << endl;
	}
    }

};


int main(int argc, char ** argv) {
    Client< master::master_spy_co > cli(argc, argv);
    cli._session().name() = "jacque";
    cli._session().addr() = "localhost";
    cli._session().port() = 9999;
    cli._session().isset() = true;
    cli.join();
    Client< master::master_cont > client(argc, argv);
    client.join();
}
