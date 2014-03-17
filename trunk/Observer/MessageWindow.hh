#ifndef _MESSAGE_WINDOW
#define _MESSAGE_WINDOW

/**
 *Classe qui affiche une fenetre de type QDialog
 *Propose à l'utilisateur d'envoyer un message
*/

#include <map>
#include <string>

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>

#include "../Net.hh"

namespace observer {

    class session_on_observer;

    class MessageWindow : public QDialog {

	Q_OBJECT

    public:
	MessageWindow(std::map<std::string, Client<session_on_observer>* > *map_spy);

    public slots:
	void send_msg();

    private:
	QVBoxLayout * main_layout;
	QHBoxLayout * buttons_layout;

	QLabel * title_label;
	QTextEdit * text_area;
	QPushButton * send_button;
	QPushButton * close_button;

	std::map<std::string, Client<session_on_observer>* > *m_map_spy;
    };
};
#endif
