#include "protocol.hh"
#include "Message.hh"
using namespace std;

Protocol::Protocol(int sock): my_stream(sock) {
    m_sock = sock;
}

void Protocol::send_msg(Message &m, string content) {
    stringstream ss(content);
    string format = m.get_format();
    my_stream << format.c_str() << m.get_name().c_str();
    for ( int i = 2 ; i < format.length() ; i++ ) {
	if ( format[i] <= '9' && format[i] >= '0' ) {
	    for ( int j = 0 ; j < format[i] - '0' ; j++ ) {
		switch( format[i + 1] ) {
		case 'i' : int a;
		    if ( !ss.eof() ) {
			ss >> a;
			my_stream << a;
		    }
		    break;
		case 'c': char c;
		    if ( !ss.eof() ) {
			ss >> c;
			my_stream << c;
		    } 
		    break;
		case 's':
		    if ( !ss.eof() ) {
			string m;
			ss >> m;
			my_stream << m.c_str();
		    }
		    break;
		case 'a': string tmp;
		    if ( !ss.eof() ) {
			tmp = ss.str().substr(my_stream.length() - m.get_name().length() - 1, ss.str().length());
			my_stream << tmp.c_str();
		    }
		    break;
		}
	    }
	}
    }
    if ( !my_stream.send() ) {
	cout << "[ERROR] -> message mal forme" << endl;
	my_stream.clean();
    }
}

string Protocol::wait(Message &m) {
    stringstream total("");
    string format = m.get_format();
    for ( int i = 2 ; i < format.length() ; i++ ) {
	if ( format[i] <= '9' && format[i] >= '0' ) {
	    for ( int j = 0 ; j < format[i] - '0' ; j++ ) {
		if ( format[i + 1] == 'a' ) {
		    string msg;
		    my_stream >> msg;
		    while ( msg != "//end//" ) {
			total << msg << " ";
			my_stream >> msg;
		    }
		} else if ( format[i + 1] == 'i' ) {
		    int a;
		    my_stream >> a;
		    total << a << " "; 
		} else if ( format[i + 1] == 'c' ) {
		    char c;
		    my_stream >> c;
		    cout << c << endl;
		    total << c << " "; 
		} else if ( format[i + 1] == 's' ) {
		    string m;
		    my_stream >> m;
		    total << m << " ";
		    
		}
	    }
	}
    }
    return total.str();  
}



Message & Protocol::operator[](string key) {
    return *message[key];
}
