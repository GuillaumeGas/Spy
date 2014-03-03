#include "MessageWindow.hh"

MessageWindow::MessageWindow() {
  main_layout = new QVBoxLayout;
  buttons_layout = new QHBoxLayout;

  title_label = new QLabel("<h2 align=\"center\">Envoie d'un message a tous les etudiants de la salle<br> info01</h2>");
  main_layout->addWidget(title_label);

  text_area = new QTextEdit;
  main_layout->addWidget(text_area);

  send_button = new QPushButton("Envoyer");
  close_button = new QPushButton("Fermer");
  buttons_layout->addWidget(send_button);
  buttons_layout->addWidget(close_button);

  main_layout->addLayout(buttons_layout);

  setLayout(main_layout);
  resize(350, 450);

  connect(close_button, SIGNAL(clicked()), this, SLOT(accept()));
}