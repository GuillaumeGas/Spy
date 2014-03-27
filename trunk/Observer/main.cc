#include <QApplication>
#include "Observer.hh"
#include "Miniature.hh"
#include <iostream>
#include <fstream>
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
  map < string, pair < string, int> > & map_spy = obs.get_map();
  QMap<QString, observer::Miniature*> & map_station = obs.get_map_stations();
  map < string, Client<observer::session_on_observer> * > & client = obs.get_map_client();
  
  for ( auto it : map_spy ) {
      client[it.first] = new Client<observer::session_on_observer>(it.second.first, it.second.second);
      client[it.first]->_session().set_name(it.first);
      client[it.first]->_session().img_recv.connect(boost::bind(&observer::Observer::update_img_screenshot, &obs, _1, _2));
      client[it.first]->_session().proc_recv.connect(boost::bind(&observer::Observer::proc_detected, &obs, _1));
      map_station[QString(it.first.c_str())] = new observer::Miniature("../img/def.bmp", it.second.first.c_str(), it.first.c_str(), client[it.first]);
      client[it.first]->_session().lst_proc_recv.connect(boost::bind(&observer::Observer::lst_proc_recved, &obs, _1, _2));
      client[it.first]->_session().res_cmd_recv.connect(boost::bind(&observer::Observer::res_cmd_recved, &obs, _1, _2));

      QObject::connect( &obs, SIGNAL(sig_set_screen(QString, QString)), map_station[QString(it.first.c_str())], SLOT(slot_set_screen(QString,QString)));
      QObject::connect( &obs, SIGNAL(sig_reset_style()), map_station[QString(it.first.c_str())], SLOT(slot_reset_style()));
      QObject::connect( &obs, SIGNAL(sig_proc_detected(QString)), map_station[QString(it.first.c_str())], SLOT(slot_proc_detected(QString)));
      QObject::connect( &obs, SIGNAL(sig_proc_list(QString, QString)), map_station[QString(it.first.c_str())], SLOT(slot_proc_list(QString,QString)));
      QObject::connect( &obs, SIGNAL(sig_cmd_recv(QString,QString)), map_station[QString(it.first.c_str())], SLOT(slot_cmd_recv(QString, QString)));
  }
  
  obs.Init_all();
  
  obs.show();
  
  return app.exec();
}

