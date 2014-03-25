#include <iostream>
#include "Miniature.hh"
#include "client.hh"

using namespace std;

namespace observer {
    Miniature::Miniature(const char * _file, const char * _station, const char * _user, Client<session_on_observer>* client) {
	m_station = _station;
	m_user    = _user;
	m_client  = client;

	station_win = NULL;

	main_layout = new QVBoxLayout;

	m_img = new QLabel;
	m_img->setPixmap(QPixmap(_file));

	QString station = "<center><b>";
	station += _station;
	station += "</b></center>";
	m_station_label = new QLabel(station);

	QString user = "<center><b>";
	user += _user;
	user += "</b></center>";
	m_user_label = new QLabel(user);

	main_layout->addWidget(m_img);
	main_layout->addWidget(m_station_label);
	main_layout->addWidget(m_user_label);

	setLayout(main_layout);
	setStyleSheet("QWidget:hover{background-color: #808080;}");
    }

    void Miniature::mouseReleaseEvent(QMouseEvent * e) {
	station_win = new StationWindow(m_station, m_user, m_client);
	station_win->exec();
	delete station_win;
	station_win = NULL;
    }

    void Miniature::set_hover_style(QString style) {
	setStyleSheet("QWidget:hover{"+style+"}");
    }

    void Miniature::set_style(QString style) {
	setStyleSheet("QWidget{"+style+"}");
    }

    void Miniature::set_img(QString file) {
	//std::cout << "file : " << file.toStdString() << std::endl;
	m_img->setPixmap(QPixmap(file));
    }

    void Miniature::slot_set_screen(QString name, QString file) {
	//std::cout << "test2 : "<< std::endl;
	if(name == m_user) {
	    //std::cout << "file : " << file.toStdString() << std::endl;
	    m_img->setPixmap(QPixmap(file));
	}
    }

    void Miniature::slot_reset_style() {
	setStyleSheet("QWidget:hover{background-color: #808080;}");
    }


    void Miniature::slot_proc_detected(QString name) {
	if ( name == m_user ) {
	    set_style("background-color: red;");
	}
    }

    void Miniature::set_proc_list(QMap<int, QString> list) {
	if(station_win) {
	
	}
    }

    void Miniature::set_cmd(QString data) {
	if(station_win) {
	
	}
    }


    void Miniature::slot_cmd_recv(QString name, QString cmd) {
	if ( m_user == name ) {
	    station_win->set_cmd(cmd);
	}
    }


    void Miniature::slot_proc_list(QString _list, QString name) {
	if ( m_user == name ) {
	    //construction QMap
	    stringstream ss(_list.toStdString());
	    QMap<int, QString> list;
	    while(!ss.eof()) {
		int pid;
		string tmp;
		ss >> pid;
		ss >> tmp;
		list[pid] = QString(tmp.c_str());
		
		//	    cout << pid << " " << list[pid] << endl;
	    }
	    station_win->set_list_proc(list);
	}
    }


};
