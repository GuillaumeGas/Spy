#include "../include/Annotation.hh"
using namespace std;

Annotation::Annotation ( ) {
    active_I = active_E = active_W = true;
}


void Annotation::show ( Annotation::Flags f, string info ) {
    switch ( f ) {
    case INFO:
	if ( active_I ) {
	    cout << "[INFO] -> " << info << endl;
	}
	break;
    case ERROR:
	if ( active_E ) {
	    cout << "[ERROR] -> " << info << endl;
	}
	break;
    case WARNING:
	if ( active_W ) {
	    cout << "[WARNING] -> " << info << endl;
	}
	break;	
    }
}


void Annotation::unactive ( Annotation::Flags f ) {
    switch ( f ) {
    case INFO: active_I = false; break;
    case ERROR: active_E = false; break;
    case WARNING: active_W = false; break;
    }
}



void Annotation::reactive ( Annotation::Flags f ) {
    switch ( f ) {
    case INFO: active_I = true; break;
    case ERROR: active_E = true; break;
    case WARNING: active_W = true; break;
    }
}


void Annotation::unactive_all ( ) {
    active_I = active_E = active_W = false;
}

void Annotation::reactive_all ( ) {
    active_I = active_E = active_W = true;
}




