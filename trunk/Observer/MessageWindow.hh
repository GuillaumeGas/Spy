#ifndef _MESSAGE_WINDOW
#define _MESSAGE_WINDOW

/**
 *Classe qui affiche une fenetre de type QDialog
 *Propose à l'utilisateur d'envoyer un message
*/

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>

class MessageWindow : public QDialog {
public:
  MessageWindow();

private:
  QVBoxLayout * main_layout;
  QHBoxLayout * buttons_layout;

  QLabel * title_label;
  QTextEdit * text_area;
  QPushButton * send_button;
  QPushButton * close_button;
};

#endif
