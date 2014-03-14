#include "Observer.hh"

using namespace std;

namespace observer {
    Observer::Observer(int argc, char** argv) : cli_master(argc, argv) {

	bool room_ok = ask_room();

	if(room_ok) {
  
	    create_network_connections();
	    init_data();
	    create_window();
      
	} else{
	    QMessageBox::critical(this, "Erreur", "Une erreur s'est produite lors de la connexion a la salle.");
	}
    }

    bool Observer::ask_room() {
	/* Liste de test */
	QStringList lst;
	lst << "info21" << "info22" << "info23" "info24" << "info25" << "info26" << "info27";

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

	message_window = new MessageWindow;
	setting_proc_win = new SettingProcWindow(&m_lst_proc);

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

    void Observer::create_network_connections() {
	for(auto it : map_spy_info) {
	    cout << "user : " << it.first << endl;
	    map_spy[it.first] = new Client<session_on_observer>(it.second.first, it.second.second);
	    map_spy[it.first]->_session().set_name(it.first);
	    map_spy[it.first]->_session().img_recv.connect(boost::bind(&Observer::update_img_screenshot, this, _1, _2));
	    map_stations[QString(it.first.c_str())] = new Miniature("img.bmp", it.second.first.c_str(), it.first.c_str());
	}
	cout << "fun create network" << endl;

	boost::thread th(boost::bind(&Observer::update_screenshots, this));
	th.detach();
    }



    void Observer::update_screenshots() {
	cout << "debut" << endl;
	//while(1) {
	    for(auto it : map_spy) {
		cout << "test" << endl;
		it.second->_session().proto->operator[]("GET_SCREENSHOT")("0.5");
	    }
	    //}
    }

    void Observer::update_img_screenshot(string name, string img) {
	auto it = map_stations.find(QString(name.c_str()));
	if(it != map_stations.end()) {
	    it.value()->set_img(QString(img.c_str()));
	    cout << "mise à jour de " << name << " - " << img << endl;
	}
    }

};
