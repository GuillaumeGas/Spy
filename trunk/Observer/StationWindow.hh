#ifndef _STATION_WIN
#define _STATION_WIN

/**
 *  Classe affichant une image taille originale du poste de l'utilisateur.
 *  Si une activité particulière a été détectée, elle est affichée
 *  Trois boutons principaux : envoyer un msg au user, afficher les processus en cours sur sa machine, executer une commande sur son poste
 */

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>

#include "MessageWindow.hh"
#include "ListProcWindow.hh"
#include "CmdWindow.hh"

class StationWindow : public QDialog {

public:
  StationWindow(QString _station, QString _user);

private:
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
};

#endif
