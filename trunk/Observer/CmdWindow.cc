#include "CmdWindow.hh"

CmdWindow::CmdWindow(QString _station) {

  main_layout = new QVBoxLayout;
  line_edit_layout = new QHBoxLayout;

  title_label = new QLabel("<h1 align=\"center\">Ligne de commande - Poste " + _station + "</h1>");
  main_layout->addWidget(title_label);

  text_edit = new QTextEdit;
  main_layout->addWidget(text_edit);

  line_edit = new QLineEdit;
  button_send = new QPushButton("Executer"); /* TODO : obj héritant de qlineedit + surcharge des events pour virer le bouton executer */
  line_edit_layout->addWidget(line_edit);
  line_edit_layout->addWidget(button_send);
  main_layout->addLayout(line_edit_layout);

  button_close = new QPushButton("Fermer");
  main_layout->addWidget(button_close);

  setLayout(main_layout);
  
  connect(button_send, SIGNAL(clicked()), this, SLOT(exec_cmd()));
  connect(button_close, SIGNAL(clicked()), this, SLOT(accept()));

}

void CmdWindow::exec_cmd() {
  std::string cmd = (line_edit->text()).toStdString();
  Cmd::exec(cmd.c_str());
  std::string res = Cmd::get_res();
  text_edit->append(QString(res.c_str()));
}
