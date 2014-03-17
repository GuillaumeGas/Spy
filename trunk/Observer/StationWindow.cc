#include "StationWindow.hh"

namespace observer {
    StationWindow::StationWindow(QString _station, QString _user) {

	m_station = _station;
	m_user    = _user;

	main_layout = new QVBoxLayout;
	buttons_layout = new QHBoxLayout;

	title_label = new QLabel("<h1 align=\"center\">Poste " + m_station + " - " + m_user + "</h1>");
	main_layout->addWidget(title_label);

	img_label = new QLabel;
	img_label->setPixmap(QPixmap("screen.bmp"));
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
  
    }
};
