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

namespace observer {

    class session_on_observer;

    class MessageWindow : public QDialog {

	Q_OBJECT

    public:
	MessageWindow(QString room, std::map<std::string, Client<session_on_observer>* > *map_spy);
	MessageWindow(QString name, Client<session_on_observer>* spy);									    
				      
    public slots:
	void send_msg();
	//void set_checkbox();

    private:
	void create_window();

	QString m_room;
	QString m_name;

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
	Client<session_on_observer>* m_spy;
    };
};
#endif
