#ifndef _OBSERVER
#define _OBSERVER

#include <iostream>
#include <vector>

#include <QApplication>
#include <QMainWindow>
#include <QStringList>
#include <QString>
#include <QInputDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVector>
#include <QScrollArea>
#include <QDesktopWidget>

#include "Miniature.hh"
#include "MessageWindow.hh"
#include "SettingProcWindow.hh"

class Observer : public QMainWindow{

  Q_OBJECT

public:
  Observer();

  bool ask_room();

private slots:
  void change_room_slot();

private:
  QString m_room;
  QVector<QString> m_lst_proc; //list proc a surveiller

  /* Elements d'affichage */
  QWidget * window;
  MessageWindow * message_window; //Fenetre type QDialog pour envoyer msg aux etu
  SettingProcWindow * setting_proc_win;

  QVBoxLayout * main_layout;
  QHBoxLayout * menu_layout;
  QGridLayout * grid_layout;
  QScrollArea * scroll; //contient le content
  QWidget     * content; //contient le grid_layout

  QLabel * title;
  QPushButton * button_sendMsg;
  QPushButton * button_changeRoom;
  QPushButton * button_settingProc;
  QPushButton * button_quit;
  
  QVector<Miniature*> vec_stations;
  /* Fin éléments d'affichage */

  void create_window();
  void create_title();
  void create_menu();
  void create_grid();
  void create_connections(); //connect les boutons...
  void init_data();


};

#endif
