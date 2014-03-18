#include <QApplication>
#include "Observer.hh"
#include <iostream>
using namespace std;


void load_file_args ( string & ip, int &mast_port, string file_name) {
    ifstream file (file_name.c_str() );
    string aux;
    while ( !file.eof() ) {
	file >> aux;
	if ( aux == "mast_ip=" ) {
	    file >> ip;
	} else if ( aux == "mast_port=" ) {
	    file >> mast_port;
	} 
    }
    if ( ip == "") {
	ip = "localhost";
    } 
    if ( mast_port == -1 ) {
	mast_port = 4444;
    }
    
}



string get_file_name(int argc, char ** argv) {
    for (int i = 0 ; i < argc - 1 ; i++) {
	if ( strcmp ( argv[i], "-f" ) == 0) {
	    return argv[i+1];
	}
    }
    return "../def.conf";
}




int main(int argc, char** argv) {
  QApplication app(argc, argv);
  int mast_port = -1;
  string mast_ip = "localhost";
  load_file_args( mast_ip, mast_port, get_file_name(argc, argv));
  observer::Observer obs(mast_ip, mast_port);
  obs.show();
  
  return app.exec();
}

