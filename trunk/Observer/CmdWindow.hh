#ifndef _CMD_WIN
#define _CMD_WIN

/**
 *  Classe permettant à l'utilisateur d'executer des commandes sur un poste
 */

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>

/* Test */
#include "../Spy/Cmd.hh"

class CmdWindow : public QDialog {

  Q_OBJECT

public:
  CmdWindow(QString _station);

private slots:
  void exec_cmd();

private:
  QVBoxLayout * main_layout;
  QHBoxLayout * line_edit_layout;

  QLabel * title_label;
  QTextEdit * text_edit;
  QLineEdit * line_edit;
  QPushButton * button_send;
  QPushButton * button_close;

};

#endif
