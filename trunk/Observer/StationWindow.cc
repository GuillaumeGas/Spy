#include "StationWindow.hh"
#include "client.hh"

using namespace std;

namespace observer {
    StationWindow::StationWindow(QString _station, QString _user, Client<session_on_observer>* client) {

	m_station = _station;
	m_user    = _user;
	m_client  = client;
	m_client->_session().proto->operator[]("GET_BIG_SCREENSHOT")("0.5");

	message_window  = NULL;
	lst_proc_window = NULL;
	cmd_window      = NULL;

	main_layout = new QVBoxLayout;
	buttons_layout = new QHBoxLayout;

	title_label = new QLabel("<h1 align=\"center\">Poste " + m_station + " - " + m_user + "</h1>");
	main_layout->addWidget(title_label);

	img_label = new QLabel;
	img_label->setPixmap(QPixmap("img.bmp"));
	main_layout->addWidget(img_label);
  
	if(client->_session().get_pid_detected() != -1) {
	    activity_label = new QLabel("Activite detectee : <font color=\"red\">[" + QString::number(client->_session().get_pid_detected()) + "] " + QString(client->_session().get_proc_detected().c_str()) + "</font>");
	    client->_session().set_pid_detected(-1);
	} else {
	    activity_label = new QLabel("Aucune activite detecte.");
	}
	main_layout->addWidget(activity_label);

	button_sendMsg = new QPushButton("Envoyer un message");
	buttons_layout->addWidget(button_sendMsg);

	button_checkProc = new QPushButton("Afficher processus en cours");
	buttons_layout->addWidget(button_checkProc);

	button_cmd = new QPushButton("Ligne de commande");
	buttons_layout->addWidget(button_cmd);

	main_layout->addLayout(buttons_layout);

	button_close = new QPushButton("Fermer");
	main_layout->addWidget(button_close);

	setLayout(main_layout);
	setWindowIcon(QIcon("iconSPY.png"));

	connect(button_sendMsg, SIGNAL(clicked()), this, SLOT(open_msgWin()));
	connect(button_checkProc, SIGNAL(clicked()), this, SLOT(open_procWin()));
	connect(button_cmd, SIGNAL(clicked()), this, SLOT(open_cmdWin()));
	connect(button_close, SIGNAL(clicked()), this, SLOT(accept()));
	//connect(button_close, SIGNAL(clicked()), this, SLOT(slot_close()));
	//connect(this, SIGNAL(sig_set_screen()), this, SLOT(slot_set_screen()));

	/*m_client->_session().big_img_recv.connect(boost::bind(&StationWindow::update_img_screenshot, this, _1));
	boost::thread th(boost::bind(&StationWindow::update_screenshots, this));
	th.detach();*/

	img_label->setPixmap(QPixmap(m_user + "_big.bmp"));

  
    }

    StationWindow::~StationWindow() {
	//m_client->_session().big_img_recv.disconnect(boost::bind(&StationWindow::update_img_screenshot, this));
    }

    void StationWindow::open_msgWin() {
	message_window = new MessageWindow(m_user, m_client);
	message_window->exec();
	delete message_window;
	message_window = NULL;
    }
    void StationWindow::open_procWin() {
	lst_proc_window = new ListProcWindow(m_station, m_client);
	lst_proc_window->exec();
	delete lst_proc_window;
	lst_proc_window = NULL;
    }
    void StationWindow::open_cmdWin() {
	cmd_window = new CmdWindow(m_station);
	cmd_window->exec();
	delete cmd_window;
	cmd_window = NULL;
    }

    /*void StationWindow::update_screenshots() {
	while(1) {
	    sleep(1);
	    m_client->_session().proto->operator[]("GET_BIG_SCREENSHOT")("0.5");
	}
    }

    void StationWindow::update_img_screenshot(string file) {
	if(open) {
	    m_file = QString(file.c_str());
	    sig_set_screen();
	}
    }

    void StationWindow::slot_set_screen() {
	img_label->setPixmap(QPixmap(m_file));
    }

    void StationWindow::slot_close() {
	open = false;
	hide();
	}*/

    void StationWindow::set_list_proc(QMap<int, QString> list) {
	cout << "              ok 2!!!!!!!! " << endl;
	if(lst_proc_window) {
	    lst_proc_window->set_list_proc(list);
	} else {
	    cout << "shèèèèèèèè" << endl;
	}
    }
};
