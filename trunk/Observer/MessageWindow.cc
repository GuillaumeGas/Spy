#include "MessageWindow.hh"
#include "client.hh"

namespace observer {
    MessageWindow::MessageWindow(map<string, Client<session_on_observer>* > *map_spy) : m_map_spy(map_spy) {
	main_layout = new QVBoxLayout;
	buttons_layout = new QHBoxLayout;
	check_layout = new QHBoxLayout;

	title_label = new QLabel("<h2 align=\"center\">Envoie d'un message a tous les etudiants de la salle<br> info01</h2>");
	main_layout->addWidget(title_label);

	text_area = new QTextEdit;
	main_layout->addWidget(text_area);

	check_info_label = new QLabel("Information : ");
	check_info = new QCheckBox;
	check_warning_label = new QLabel("Avertissement : ");
	check_warning = new QCheckBox;
	check_layout->addWidget(check_info_label);
	check_layout->addWidget(check_info);
	check_layout->addWidget(check_warning_label);
	check_layout->addWidget(check_warning);
	main_layout->addLayout(check_layout);

	send_button = new QPushButton("Envoyer");
	close_button = new QPushButton("Fermer");
	buttons_layout->addWidget(send_button);
	buttons_layout->addWidget(close_button);

	main_layout->addLayout(buttons_layout);

	setLayout(main_layout);
	resize(350, 450);

	//connect(check_info, SIGNAL(stateChanged()), this, SLOT(set_checkbox()));	//connect(check_warning, SIGNAL(stateChanged()), this, SLOT(set_checkbox()));
	connect(send_button, SIGNAL(clicked()), this, SLOT(send_msg()));
	connect(close_button, SIGNAL(clicked()), this, SLOT(accept()));
    }

    void MessageWindow::send_msg() {
	QString msg = text_area->toPlainText();
	msg += " //end//";

	for(auto it : *m_map_spy) {
	    if(check_info->isChecked()) {
		it.second->_session().proto->operator[]("INFO")(msg.toStdString());
	    } else {
		it.second->_session().proto->operator[]("WARNING")(msg.toStdString());
	    }
	}
    }

    
};
