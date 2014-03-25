#ifndef _STATION_WIN
#define _STATION_WIN

/**
 *  Classe affichant une image taille originale du poste de l'utilisateur.
 *  Si une activité particulière a été détectée, elle est affichée
 *  Trois boutons principaux : envoyer un msg au user, afficher les processus en cours sur sa machine, executer une commande sur son poste
 */

#include <iostream>

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QMap>

#include "MessageWindow.hh"
#include "ListProcWindow.hh"
#include "CmdWindow.hh"

#include "../Net.hh"

namespace observer {

    class session_on_observer;

    class StationWindow : public QDialog {

	Q_OBJECT

    public:
	StationWindow(QString _station, QString _user, Client<session_on_observer>* client);
	~StationWindow();

	void set_list_proc(QMap<int, QString> list);
	void set_cmd(QString);

    public slots:
	void open_msgWin();
	void open_procWin();
	void open_cmdWin();
	//void slot_set_screen();
	//void slot_close();

	//signals:
	//void sig_set_screen();

    private:
	void update_screenshots();
	void update_img_screenshot(std::string);

	QVBoxLayout * main_layout;
	QHBoxLayout * buttons_layout;

	QLabel * title_label;
	QLabel * img_label;
	QLabel * activity_label;
	QPushButton * button_sendMsg;
	QPushButton * button_checkProc;
	QPushButton * button_cmd;
	QPushButton * button_close;

	MessageWindow * message_window;
	ListProcWindow * lst_proc_window;
	CmdWindow * cmd_window;

	QString m_station;
	QString m_user;
	//QString m_file;
	Client<session_on_observer>* m_client;

	//bool open;
    };
};
#endif
