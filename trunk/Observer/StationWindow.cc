#include "StationWindow.hh"
#include "client.hh"

using namespace std;

namespace observer {
    StationWindow::StationWindow(QString _station, QString _user, Client<session_on_observer>* client) {

	m_station = _station;
	m_user    = _user;
	m_client  = client;

	main_layout = new QVBoxLayout;
	buttons_layout = new QHBoxLayout;

	title_label = new QLabel("<h1 align=\"center\">Poste " + m_station + " - " + m_user + "</h1>");
	main_layout->addWidget(title_label);

	img_label = new QLabel;
	img_label->setPixmap(QPixmap("img.bmp"));
	main_layout->addWidget(img_label);
  
	activity_label = new QLabel("Activite detectee : <font color=\"red\">Firefox</font>");
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

	//message_window  = new MessageWindow;
	lst_proc_window = new ListProcWindow(m_station); 
	cmd_window      = new CmdWindow(m_station);

	//connect(button_sendMsg, SIGNAL(clicked()), message_window, SLOT(exec()));
	connect(button_checkProc, SIGNAL(clicked()), lst_proc_window, SLOT(exec()));
	connect(button_cmd, SIGNAL(clicked()), cmd_window, SLOT(exec()));
	connect(button_close, SIGNAL(clicked()), this, SLOT(accept()));
	connect(this, SIGNAL(sig_set_screen(QString)), this, SLOT(slot_set_screen(QString)));

	m_client->_session().big_img_recv.connect(boost::bind(&StationWindow::update_img_screenshot, this, _1));
	boost::thread th(boost::bind(&StationWindow::update_screenshots, this));
	th.detach();
  
    }

    StationWindow::~StationWindow() {
	m_client->_session().big_img_recv.disconnect(&StationWindow::update_img_screenshot);
    }

    void StationWindow::update_screenshots() {
	while(1) {
	    sleep(1);
	    m_client->_session().proto->operator[]("GET_SCREENSHOT")("0.5");
	}
    }

    void StationWindow::update_img_screenshot(string file) {
	emit sig_set_screen(QString(file.c_str()));
    }

    void StationWindow::slot_set_screen(QString file) {
	img_label->setPixmap(QPixmap(file));
    }
};
