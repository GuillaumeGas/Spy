#include "Stream_net.hh"
using namespace std;




Stream_net::Stream_net(int sock) {
    m_read = fdopen(sock, "r");
    m_write = fdopen(sock, "w");
}

void Stream_net::send_string( const char *  param ) {
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
	if ( m_waited_elem.back().type == "s" ) {
	    ss << m_param << " ";
	    m_waited_elem.back().nb--;
	    if ( m_waited_elem.back().nb == 0 ) {
		m_waited_elem.pop_back();
	    }
	}
    }
}


void Stream_net::show_list() {
    for ( auto it = m_waited_elem.begin() ; it != m_waited_elem.end() ; it++) {
	cout << it->type << " " << it->nb << endl;
    }
}


void Stream_net::show_elem() {
    cout << ss.rdbuf() << endl;
}