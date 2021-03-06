#ifndef _LIST_PROC_WIN
#define _LIST_PROC_WIN

/**
 *  Classe permettant d'afficher les processus en cours sur un poste
 */

#include <iostream>

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include <QHeaderView>
#include <QStringList>
#include <QMap>

#include "../Net.hh"

namespace observer {
    class session_on_observer;
    class ListProcWindow : public QDialog {
    public:
	ListProcWindow(QString _station, Client<session_on_observer> * client);

	void set_list_proc(QMap<int, QString> list);

    private:
	QVBoxLayout * main_layout;
  
	QLabel * title_label;
	QTableWidget * proc_table;
	QPushButton * button_close;
    };
};
#endif
