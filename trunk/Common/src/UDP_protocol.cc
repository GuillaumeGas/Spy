#include "../include/UDP_protocol.hh"
#include "../include/UDP_Message.hh"
#include <sstream>

UDP_Protocol::UDP_Protocol ( int & port1, int & port2 , std::string & ip ) {
    m_sendsocket = socket ( AF_INET, SOCK_DGRAM, 0 );
    m_sendsin.sin_addr.s_addr = htonl(INADDR_ANY);
    m_sendsin.sin_family = AF_INET;
    m_sendsin.sin_port = htons(port2);
    hostent * hostinfo = NULL;
    hostinfo = gethostbyname(ip.c_str());
    if ( hostinfo ) {
	m_sendsin.sin_addr = *(in_addr*)hostinfo->h_addr;
	m_host = true;
    } else {
	std::cout << "[INFO]-> Host non reconnu" << std::endl;
    }
    m_ip = ip;
    
    m_sock = socket( AF_INET, SOCK_DGRAM, 0);
    m_sin.sin_addr.s_addr = htonl(INADDR_ANY);
    m_sin.sin_family = AF_INET;
    m_sin.sin_port = htons(port1);

    if ( bind(m_sock, (sockaddr*)&m_sin, sizeof(m_sin)) == -1 ) {
	std::cout << "erreur de bind changer de port" << std::endl;
	throw m_port;
    }
}
    
using namespace std;

void UDP_Protocol::send_msg( UDP_Message & m, string msg ) {
    if ( m_host ) {
	stringstream ss(msg);
	stringstream total;
	string format = m.get_format();
	total << m.get_name() << " ";
	for ( int i = 2 ; i < format.length() ; i++ ) {
	    if ( format[i] <= '9' && format[i] >= '0' ) {
		for (int j = 0 ; j < format[i] - '0' ; j++ ) {
		    if ( format[i + 1] == 'i' ) {
			if ( !ss.eof() ) {
			    int a;
			    ss >> a;
			    total << a;
			} else {
			    a.show ( Annotation::ERROR, "Message mal forme" );
			    return;
			}
		    } else if ( format[i + 1] == 'c' ) {
			if ( !ss.eof() ) {
			    char c;
			    ss >> c;
			    total << c;
			} else {
			    a.show ( Annotation::ERROR, "Message mal forme" );
			    return;
			}
		    } else if ( format[i + 1] == 's' ) {
			if ( !ss.eof() ) {
			    string msg;
			    ss >> msg;
			    total << msg << " " ;
			} else {
			    a.show ( Annotation::ERROR, "Message mal forme" );			    
			    return;
			}
		    } else if ( format[i + 1] == 'a' ) {
			if ( !ss.eof() ) {
			    string tmp;
			    int deb = total.str().length() - m.get_name().length() - 1;
			    if ( deb < 0 ) {
				deb = 0;
			    }
			    tmp = ss.str().substr(deb, ss.str().length() );
			    total << tmp;
			} else {
			    a.show ( Annotation::ERROR, "Message mal forme" );			    			
			    return;
			}
		    }  
		}
		
	    }
	}
	if ( ss.str().length() > (total.str().length() - m.get_name().length() )  ) {
	    a.show ( Annotation::WARNING, "element superflux en fin de message" );			    			
	} 
	total << " //end//";
	if ( sendto(m_sendsocket, total.str().c_str(), total.str().length(), 0, (sockaddr*)&m_sendsin, sizeof(m_sendsin)) == -1 ) {
	    
	    a.show ( Annotation::ERROR, "Probleme envoi" );	
	} else {
	    a.show ( Annotation::INFO, "Message envoye" );	
	}
    } else {
	a.show ( Annotation::ERROR, "Host Inconnu" );	
    }
}


string UDP_Protocol::wait( UDP_Message & m ) {
    stringstream total("");
    stringstream tmp;
    string msg;
    while ( msg != "//end//" ) {
	if ( m_tmp.eof() ) {
	    char buffer[255];
	    int n = recvfrom( m_sock, buffer, 254, 0, NULL, NULL );
	    buffer[n] = 0;
	    tmp << buffer;
	    while ( !tmp.eof() ) {
		tmp >> msg;
		if ( msg == "//end//" ) {
		    return total.str();
		} else {
		    total << msg << " ";
		}
	    }
	} else {
	    while ( !m_tmp.eof() ) {
		m_tmp >> msg;
		if ( msg == "//end//" ) {
		    return total.str();
		} else {
		    total << msg << " ";
		}
	    }
	}
    }
}

void UDP_Protocol::waitmsg( string & msg ) {
    char buffer[255];
    m_tmp.clear();
    sockaddr * sin = new sockaddr;
    socklen_t sizesin = sizeof(sin);
    int n = recvfrom(m_sock, buffer, 254, 0, sin, &sizesin);
    buffer[n] = 0;
    m_tmp << buffer;
    m_tmp >> msg;
}


UDP_Message & UDP_Protocol::operator[]( string key ) {
    return *message[key];
}



void UDP_Protocol::change_write_port(int port, string ip) {
    m_sendsocket = socket ( AF_INET, SOCK_DGRAM, 0 );
    m_sendsin.sin_addr.s_addr = htonl(INADDR_ANY);
    m_sendsin.sin_family = AF_INET;
    m_sendsin.sin_port = htons(port);
    hostent * hostinfo = NULL;

    hostinfo = gethostbyname(ip.c_str());
    if ( hostinfo ) {
	m_sendsin.sin_addr = *(in_addr*)hostinfo->h_addr;
	m_host = true;
    } else {
	a.show ( Annotation::ERROR, " Host Inconnu " );
	m_host = false;
    }
}



void UDP_Protocol::unactive_annotation ( Annotation::Flags f ) {
    a.unactive ( f );
}


void UDP_Protocol::reactive_annotation ( Annotation::Flags f ) {
    a.reactive ( f );
}



void UDP_Protocol::unactive_annotation ( ) {
    a.unactive_all ( );
}

void UDP_Protocol::reactive_annotation ( ) {
    a.reactive_all ( );
}
