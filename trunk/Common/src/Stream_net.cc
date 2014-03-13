#include "../include/Stream_net.hh"
using namespace std;




Stream_net::Stream_net(int sock) {
    m_read = fdopen(sock, "r");
    m_write = fdopen(sock, "w");
}

void Stream_net::send( const char *  param ) {
    string m_param(param);
    if ( m_waited_elem.size() == 0) {
	for ( int i = 0 ; i < m_param.length() ; i++ ) {
	    if ( m_param[i] >= '0' && m_param[i] <= '9' ) {
		if ( i != m_param.length() - 1 ) {
		    m_waited_elem.push_front(typewait(m_param[i+1], m_param[i] - '0'));	   
		}
	    }
	}
    } else {
	if ( m_waited_elem.back().type == "s" || m_waited_elem.back().type == "a" ) {
	    ss << m_param << " ";
	    m_waited_elem.back().nb--;
	    if ( m_waited_elem.back().nb == 0 ) {
		m_waited_elem.pop_back();
		if ( m_waited_elem.size() == 0 ) {
		    send_msg();
		}
	    }
	}
    }
}


void Stream_net::send(int param) {
    if ( m_waited_elem.size() != 0 ) {
	if ( m_waited_elem.back().type == "i" ) {
	    ss << param << " ";
	    m_waited_elem.back().nb--;
	    if ( m_waited_elem.back().nb == 0 ) {
		m_waited_elem.pop_back();
		if (m_waited_elem.size() == 0 ) {
		    send_msg();
		}
	    }
	}
    }
}


void Stream_net::send(char param) {
    if ( m_waited_elem.size() != 0 ) {
	if ( m_waited_elem.back().type == "c" ) {
	    ss << param << " ";
	    m_waited_elem.back().nb--;
	    if ( m_waited_elem.back().nb == 0 ) {
		m_waited_elem.pop_back();
		if ( m_waited_elem.size() == 0 ) {
		    send_msg();
		}
	    }
	}
    }
}


void Stream_net::send_msg() {
    string msg(ss.str());
    fprintf( m_write, "%s\n", msg.c_str());
    fflush(m_write);
    ss.str("");
}



void Stream_net::send_string( string msg ) {
    fprintf( m_write, "%s\n", msg.c_str() );
    fflush( m_write );
}


void Stream_net::send_int ( int a ) {
    fprintf ( m_write, "%d\n", a);
    fflush( m_write );
}


void Stream_net::show_list() {
    for ( auto it = m_waited_elem.begin() ; it != m_waited_elem.end() ; it++) {
	cout << it->type << " " << it->nb << endl;
    }
}


void Stream_net::show_elem() {
    cout << ss.rdbuf() << endl;
}



string Stream_net::recv() {
    char buffer[255];
    if ( fscanf( m_read, "%s", buffer) == 1 ) {
	return string(buffer);
    } else {
	return string("");
    }
}



void Stream_net::recv(int & a) {
    if ( fscanf(m_read, "%i", &a) == 1 ) {
    } else {
	a = -1; 
    }
}

void Stream_net::recv(char & a) {
    if ( fscanf(m_read, "%c", &a) == 1 ) {
    } else {
	a = -1; 
    }
}

void Stream_net::recv_string ( int size, stringstream &ss) {

    if ( size > 20000 ) {
	char buffer[20001];
	int toRead = 20000;
	for (int i = 0 ; i < size ; i += 20000 ) {
	  if(i + 20000 > size) {
	    toRead = size-i;
	  }
	  int n;
	  if (  (n = fread ( buffer , 1 , toRead, m_read )) == 20000 ) {
		buffer[n] = 0 ;
		
		ss << buffer;
	    } else {
	      buffer[n] = 0;
	      ss << buffer;
	      break;
	    }
	}
	cout << "sortie" << endl;
    } else {
	char buffer [ size + 1 ];
	if ( fread ( buffer, 1 , size , m_read )  == size ) {
	    buffer[size] = 0;
	    ss << buffer;   
	}
    }
}

Stream_net & operator>>( Stream_net & st, string & param ) {
    param = st.recv();
    return st;
}



Stream_net & operator>>( Stream_net & st, int & a ) {
    st.recv(a);
    return st;
}


Stream_net & operator>>( Stream_net & st, char & a ) {
    st.recv(a);
    return st;
}


bool Stream_net::send() {
    return m_waited_elem.size() == 0;
}


void Stream_net::clean() {
    while ( m_waited_elem.size() != 0 ) {
	m_waited_elem.pop_back();
    }
    ss.str("");
}


string Stream_net::str() {
    return ss.str();
}

int Stream_net::length() {
    return ss.str().length();
}
