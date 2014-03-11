#include "Sniffer.hh"
#include <fstream>
using namespace std;

namespace controller {

    Sniffer::Sniffer ( string mast_ip, int mast_port, int read , int write, int salle) 	
	: snif_client ( "localhost" , read, write ) , 
	link_master ( mast_ip, mast_port ), 
	Thread < Sniffer > ( &Sniffer::loop_recv, this )  {
	
	snif_client._session().set_ip( load_hostname() ) ;
	snif_client._session().set_port( read );
	
	m_write = write;
	m_read = read;
	m_salle = salle;
	m_speed = 5000000;
	m_stop = false;
    }

    string Sniffer::load_hostname() {
	system ( "hostname > rep" );
	ifstream file ( "rep" );
	string rep;
	file >> rep;
	return rep;
    }


    void Sniffer::send_to_master ( ) {
	stringstream ss;
	ss << spy_map.size() << " " << m_salle << " " ;
	for ( auto it : spy_map ) {
	    cout << it.first << " " << it.second.first << " " << it.second.second << endl;
	    ss << it.first << " " << it.second.first << " " << it.second.second;
	}
	link_master._session().send_map ( ss );
    }


    void Sniffer::set_speed ( int speed ) {
	m_speed = speed;
    }

    void Sniffer::loop_recv() {
	stringstream ss;
	while ( !m_stop ) {
	    system ( "clear" ); 
	    for ( int i = 1 ; i < 30 ; i++ ) {
		ss.str("");
		ss << "info" << m_salle << "-";
		if ( i < 10 ) {
		    ss << "0";
		} 
		ss << i;
		cout << ss.str() << endl;
		snif_client._session().change_write_port( m_write, ss.str() );
		snif_client._session().send();
		if ( snif_client._session().received() ) {
		    spy_map[snif_client._session().recv().first] = snif_client._session().recv().second;
		    snif_client._session().reset();
		} else {
		    continue;
		}
	    }
	    send_to_master( );
	    spy_map.clear( );
	    usleep ( m_speed );
	}
    }


    void Sniffer::launch() {
	start();
	snif_client._session().start();
    }

    void Sniffer::wait() {
	join();
    }


    void Sniffer::stop() {
	m_stop = true;
    }


};
