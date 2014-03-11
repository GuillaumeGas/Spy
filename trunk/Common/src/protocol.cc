#include "../include/protocol.hh"
#include "../include/Message.hh"
#include "../include/Img_Message.hh"
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
			int deb = my_stream.length() - m.get_name().length() - 1;
			if ( deb < 0 ) {
			    deb = 0;
			}
			tmp = ss.str().substr(deb , ss.str().length());
			my_stream << tmp.c_str();
		    }
		    break;
		}
	    }
	}
    }
    if ( !my_stream.send() ) {
	a.show ( Annotation::ERROR, " Message mal forme " );
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
			cout << msg << endl;
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



Img_Message & Protocol::operator()(string key) {
    return *imessage[key];
}


void Protocol::unactive_annotation ( Annotation::Flags f ) {
    a.unactive ( f );
}


void Protocol::reactive_annotation ( Annotation::Flags f ) {
    a.reactive ( f );
}



void Protocol::unactive_annotation ( ) {
    a.unactive_all ( );
}

void Protocol::reactive_annotation ( ) {
    a.reactive_all ( );
}


void Protocol::send_img ( Img_Message & m, string content, int h, int l ) {
    my_stream.send_string ( m.get_name() );
    my_stream.send_int ( content.length() );
    my_stream.send_string ( content );
    my_stream.send_string ( " " );
    my_stream.send_int ( h );
    my_stream.send_int ( l );
} 


void Protocol::wait_msg ( Message & m ) {
    m.sig_recv ( wait ( m ) );
}


void Protocol::wait_img ( Img_Message & m ) {
    int h, l, size;
    string content;
    my_stream.recv ( size );
    content = my_stream.recv_string ( size );
    my_stream.recv( h );
    my_stream.recv( l );
    
    m.sig_recv( content , h , l );
}
