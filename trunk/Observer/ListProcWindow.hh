#ifndef _LIST_PROC_WIN
#define _LIST_PROC_WIN

/**
 *  Classe permettant d'afficher les processus en cours sur un poste
 */

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include <QHeaderView>
#include <QStringList>

class ListProcWindow : public QDialog {
public:
  ListProcWindow(QString _station);

private:
  QVBoxLayout * main_layout;
  
  QLabel * title_label;
  QTableWidget * proc_table;
  QPushButton * button_close;
};

#endif
