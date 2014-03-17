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
#include <QCheckBox>

#include "../Net.hh"
//#include "client.hh"

namespace observer {

    class session_on_observer;

    class MessageWindow : public QDialog {

	Q_OBJECT

    public:
	MessageWindow(std::map<std::string, Client<session_on_observer>* > *map_spy);

    public slots:
	void send_msg();
	//void set_checkbox();

    private:
	QVBoxLayout * main_layout;
	QHBoxLayout * check_layout;
	QHBoxLayout * buttons_layout;

	QLabel * title_label;
	QTextEdit * text_area;
	QLabel * check_info_label;
	QCheckBox * check_info;
	QLabel * check_warning_label;
	QCheckBox * check_warning;
	QPushButton * send_button;
	QPushButton * close_button;

	std::map<std::string, Client<session_on_observer>* > *m_map_spy;
    };
};
#endif
