#include "Observer.hh"

using namespace std;

namespace observer {
    Observer::Observer(int argc, char** argv) : cli_master(argc, argv) {

	bool room_ok = ask_room();

	if(room_ok) {
	} else{
	    QMessageBox::critical(this, "Erreur", "Une erreur s'est produite lors de la connexion a la salle.");
	}
    }

    Observer::Observer(string ip, int port) : cli_master(ip, port) {

	bool room_ok = ask_room();

	if(room_ok) {     
	} else{
	    QMessageBox::critical(this, "Erreur", "Une erreur s'est produite lors de la connexion a la salle.");
	}
    }

    
    
    void Observer::Init_all() {
	boost::thread th(boost::bind(&Observer::update_screenshots, this));
	th.detach();
	init_data();
	create_window();
    }

    bool Observer::ask_room() {
	/* Liste de test */
	QStringList lst;
	lst << "info21" << "info22" << "info23" << "info24" << "info25" << "info26" << "info27";

	bool ok, continuer = true;
	while(continuer) {
	    m_room = QInputDialog::getItem(this, "Observateur", "Choix de la salle :", lst, 0, false, &ok);
	    if(ok && !lst.isEmpty()) {
		/* On go tenter une connexion */
		cout << m_room.toStdString().substr(4, 7) << endl;
		cli_master._session().send(m_room.toStdString().substr(4, 7));
		while(!cli_master._session().received()) {}
		map_spy_info = cli_master._session().get_map();
		QMessageBox::information(this, "Information", "Salle selectionnee : "+m_room);
		continuer = false;
	    } else if(ok && lst.isEmpty()) {
		QMessageBox::critical(this, "Erreur.", "Aucune salle disponible.");
	    } else {
		continuer = false;
	    }
	}
	return ok;
    }

    void Observer::create_window() {

	window = new QWidget;
	main_layout = new QVBoxLayout;
	menu_layout = new QHBoxLayout;
	grid_layout = new QGridLayout;
	content     = new QWidget;

	scroll = new QScrollArea;
 
	create_title();
	create_menu();
	create_grid();

	message_window = new MessageWindow(m_room, &map_spy);
	setting_proc_win = new SettingProcWindow(&m_lst_proc, map_spy);

	create_connections();

	window->setLayout(main_layout);
	setCentralWidget(window);

	setMinimumSize(1320, 800);
	setWindowIcon(QIcon("iconSPY.png"));
	setWindowTitle("Observer");

    }

    void Observer::create_title() {
	title = new QLabel("<h1 align=\"center\">Observation de la salle " + m_room + "</h1>");
	main_layout->addWidget(title);
    }

    void Observer::create_menu() {
	button_sendMsg = new QPushButton("Envoyer un message a tous");
	button_settingProc = new QPushButton("Gerer processus a surveiller");
	button_changeRoom = new QPushButton("Changer de salle");
	button_changeRoom->setEnabled(false);
	button_quit = new QPushButton("Quitter");

	menu_layout->addWidget(button_sendMsg);
	menu_layout->addWidget(button_changeRoom);
	menu_layout->addWidget(button_settingProc);
	menu_layout->addWidget(button_quit);
	main_layout->addLayout(menu_layout);
    }

    void Observer::create_grid() {
	/*
	  insertions de test
	*/
	//map_stations["gas"] = new Miniature("img.bmp", "info28", "gas");
	/* Fin test */
  

	int x = 0, y = 0;
	QMapIterator<QString, Miniature*> i(map_stations);
	while (i.hasNext()) {
	    i.next();
	    grid_layout->addWidget(i.value(), x, y);
	    if(y == 2) {
		x++;
		y = 0;
	    } else {
		y++;
	    }
	}

	content->setLayout(grid_layout);
	scroll->setWidget(content);
	main_layout->addWidget(scroll);
    }

    void Observer::create_connections() {
	connect(button_sendMsg, SIGNAL(clicked()), message_window, SLOT(exec()));
	connect(button_changeRoom, SIGNAL(clicked()), this, SLOT(change_room_slot()));
	connect(button_settingProc, SIGNAL(clicked()), setting_proc_win, SLOT(exec()));
	connect(button_quit, SIGNAL(clicked()), qApp, SLOT(quit()));
    }

    void Observer::change_room_slot() {
	bool room_ok = ask_room();

	if(room_ok) {
  
	    /* Mise à jour de l'interface */
	    /* ERREUR
	       while(vec_posts.size() > 0) {
	       Miniature * tmp = vec_posts.front();
	       delete tmp;
	       vec_posts.pop_front();
	       }

	       for(int i = 0; i < 6; i++) {
	       vec_posts.push_back(new Miniature("img2.bmp"));
	       }

	       int x = 0, y = 0;
	       for(int i = 0; i < vec_posts.size(); i++) {
	       grid_layout->addLayout(vec_posts[i], x, y);
	       if(y == 2) {
	       x++;
	       y = 0;
	       } else {
	       y++;
	       }
	       }*/

    
	} else{
	    QMessageBox::critical(this, "Erreur", "Une erreur s'est produite lors de la connexion a la salle.");
	}
    }

    void Observer::init_data() {
	m_lst_proc.push_back("Firefox");
	m_lst_proc.push_back("Teeworld");
    }


    QMap <QString, Miniature*> & Observer::get_map_stations() {
	return map_stations;
    } 

    map< string, pair<string , int> >& Observer::get_map() {
	return map_spy_info;
    }
    
    map<string, Client<session_on_observer>* > & Observer::get_map_client() {
	return map_spy;
    }
    
    void Observer::update_screenshots() {
	cout << "debut" << endl;
	while(1) {
	    sleep(1);
	    for(auto it : map_spy) {
		it.second->_session().proto->operator[]("GET_SCREENSHOT")("0.3");
	    }
	    emit sig_reset_style();
	}
    }

    void Observer::update_img_screenshot(string name, string img) {
	emit sig_set_screen(QString(name.c_str()), QString(img.c_str()));
    }

    void Observer::proc_detected(string name) {
	int i = 0;
	for(auto it : map_spy) {
	    if(it.first == name) {
		int j = 0;
		for(auto it2 = map_stations.begin(); it2 != map_stations.end(); it2++, j++) {
		    if(i == j) {
			it2.value()->set_style("background-color: red;");
			break;
		    }
		}
		break;
	    }
	    i++;
	}
    }

    void Observer::lst_proc_recved(QString name, QMap<int, QString> list) {
	auto it = map_stations.find(name);
	if(it != map_stations.end()) {
	    it.value()->set_proc_list(list);
	}
    }

    void Observer::res_cmd_recved(std::string name, std::string data) {
	auto it = map_stations.find(QString(name.c_str()));
	if(it != map_stations.end()) {
	    it.value()->set_cmd(QString(data.c_str()));
	}
    }

};
