#ifndef _OBSERVER
#define _OBSERVER

#include <iostream>

#include <QApplication>
#include <QMainWindow>
#include <QStringList>
#include <QString>
#include <QInputDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QPushButton>


class Observer : public QMainWindow{

public:
  Observer();

  bool ask_room();

private:
  QString m_room;

  /* Elements d'affichage */
  QWidget * window;

  QVBoxLayout * main_layout;
  QHBoxLayout * menu_layout;

  QLabel * title;
  QPushButton * button_sendMsg;
  QPushButton * button_changeRoom;
  QPushButton * button_quit;
  /* Fin éléments d'affichage */

  void create_window();
  void create_title();
  void create_menu();
  //void create_grid();

  void create_connections(); //connect les boutons...

};

#endif
