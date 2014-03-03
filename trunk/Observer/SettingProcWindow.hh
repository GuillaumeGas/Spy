#ifndef _SETTING_PROC_WIN
#define _SETTING_PROC_WIN

/* Classe qui affiche une fenetre proposant à l'utilisateur d'ajouter des processus à surveiller, et affiche ceux déjà enregistrés */

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QStringList>
#include <QHeaderView>
#include <QMessageBox>

class SettingProcWindow : public QDialog {

  Q_OBJECT

public:
  SettingProcWindow();

private slots:
  void add_to_procTable();

private:
  QVBoxLayout * main_layout;
  QHBoxLayout * buttons_layout;

  QLabel * title_label;
  QTableWidget * proc_table;
  QLineEdit * line_edit;
  QPushButton * button_addProc;
  QPushButton * button_close;

};

#endif
