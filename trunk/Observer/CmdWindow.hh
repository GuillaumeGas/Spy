#ifndef _CMD_WIN
#define _CMD_WIN

/**
 *  Classe permettant à l'utilisateur d'executer des commandes sur un poste
 */

#include <iostream>
#include <sstream>

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QKeyEvent>
#include <QMessageBox>

/* Test */
//#include "../Spy/Cmd.hh"
#include "../Net.hh"

namespace observer {
    class session_on_observer;
    class CmdWindow : public QDialog {

	Q_OBJECT

	public:
	CmdWindow(QString _station, Client<session_on_observer> * client);
	void set_cmd(QString);

    private slots:
	void exec_cmd();

    private:
	void keyPressEvent(QKeyEvent *event);
	QString get_prev_cmd();
	QString get_next_cmd();

	QVBoxLayout * main_layout;

	QLabel * title_label;
	QTextEdit * text_edit;
	QLineEdit * line_edit;
	QPushButton * button_close;

	Client<session_on_observer> * m_client;

	//	Cmd m_cmd;
	QVector<QString> lst_cmd;
	int pos;
	QString m_station;
    };
};
#endif
