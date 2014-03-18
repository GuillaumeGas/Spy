#include "controller.hh"
#include "../Master/client.hh"
#include "Sniffer.hh"
#include <sstream>
#include <fstream>

using namespace std;

namespace controller {


    controller_session::controller_session ( int & write, int & read, string & ip )
	: Client_UDPSession ( write, read, ip ) {
	proto = new cont_proto ( write, read, ip );
	(*proto)["YES"].sig_recv.connect( boost::bind ( &controller_session::do_YES, this, _1));
	sig_begin.connect(boost::bind( &controller_session::on_begin, this));
    }

    void controller_session::on_begin() {
    }


    void controller_session::send() {
	stringstream ss;
	ss << m_ip << " " << m_port;
	(*proto)["HERE?"](ss.str());
    }


    void controller_session::set_ip( string ip ) {
	cout << ip << endl;
	m_ip = ip;
    }

    void controller_session::set_port ( int port )  {
	m_port = port;
    }


    void controller_session::do_YES ( string msg ) {
	stringstream ss(msg);
	ss >> name >> ip >> port;
	cout << "[SYS] -> Yes " << name << " " << ip << ":" << port << endl;
	m_recv = true;
    }
    
    bool controller_session::received() {
	return m_recv;
    }
    
    string controller_session::info() {
	return m_info;
    }


    pair < string , pair < string, int > > controller_session::recv() {
	pair < string , pair < string, int > > p;
	p.first = name;
	p.second.first = ip;
	p.second.second = port;
	return p;
    }
    

    void controller_session::reset() {
	m_recv = false;
    }

};


void check(string & ip, int &port1, int &port2, int &port3, int & salle, int & speed) {
    if ( ip == "" ){
	ip = "localhost";
    } 
    if ( port1 == -1 ) {
	port1 = 4444;
    }
    if ( port2 == -1 ) {
	port2 = 9999;
    }
    if ( port3 == -1 ) {
	port3 = 9999;
    }
    if (salle == -1 ) {
	salle = 27;
    }
    if (speed == -1 ){
	speed = 5;
    }
}




void load_file_args ( string & ip, int &mast_port, int &this_port, int &write_port , int & salle, int & speed, string file_name) {
    ifstream file (file_name.c_str() );
    string aux;
    while ( !file.eof() ) {
	file >> aux;
	if ( aux == "mast_ip=" ) {
	    file >> ip;
	} else if ( aux == "mast_port=" ) {
	    file >> mast_port;
	} else if ( aux == "cont_port=") {
	    file >> this_port;
	} else if ( aux == "spy_read_port=") {
	    file >> write_port;
	} else if ( aux =="salle=" ) {
	    file >> salle;
	}else if ( aux == "speed=" ){
	    file >> speed;
	}
    }
    check( ip, mast_port, this_port, write_port, salle, speed);
    
}



string get_file_name(int argc, char ** argv) {
    for (int i = 0 ; i < argc - 1 ; i++) {
	if ( strcmp ( argv[i], "-f" ) == 0) {
	    return argv[i+1];
	}
    }
    return "../def.conf";
}



int main(int argc, char ** argv) {
    string ip = "";
    int mast_port, this_port, write_port, salle, speed;
    mast_port = this_port = write_port = salle = speed = -1;
    load_file_args ( ip, mast_port, this_port, write_port, salle, speed, get_file_name ( argc, argv) );
    
    controller::Sniffer s ( ip, mast_port, this_port, write_port, salle, speed );
    s.launch();
    s.join();
}
