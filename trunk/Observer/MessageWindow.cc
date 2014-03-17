#include "MessageWindow.hh"
#include "client.hh"

namespace observer {
    MessageWindow::MessageWindow(map<string, Client<session_on_observer>* > *map_spy) : m_map_spy(map_spy) {
	main_layout = new QVBoxLayout;
	buttons_layout = new QHBoxLayout;

	title_label = new QLabel("<h2 align=\"center\">Envoie d'un message a tous les etudiants de la salle<br> info01</h2>");
	main_layout->addWidget(title_label);

	text_area = new QTextEdit;
	main_layout->addWidget(text_area);

	send_button = new QPushButton("Envoyer");
	close_button = new QPushButton("Fermer");
	buttons_layout->addWidget(send_button);
	buttons_layout->addWidget(close_button);

	main_layout->addLayout(buttons_layout);

	setLayout(main_layout);
	resize(350, 450);

	connect(send_button, SIGNAL(clicked()), this, SLOT(send_msg()));
	connect(close_button, SIGNAL(clicked()), this, SLOT(accept()));
    }

    void MessageWindow::send_msg() {
	QString msg = text_area->toPlainText();
	msg += " //end//";

	for(auto it : *m_map_spy) {
	    it.second->_session().proto->operator[]("INFO")(msg.toStdString());
	}
    }
};
