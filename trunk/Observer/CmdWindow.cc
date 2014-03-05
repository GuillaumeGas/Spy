#include "CmdWindow.hh"

CmdWindow::CmdWindow(QString _station) : pos(0){

  main_layout = new QVBoxLayout;

  title_label = new QLabel("<h1 align=\"center\">Ligne de commande - Poste " + _station + "</h1>");
  main_layout->addWidget(title_label);

  text_edit = new QTextEdit;
  main_layout->addWidget(text_edit);

  line_edit = new QLineEdit;
  main_layout->addWidget(line_edit);

  button_close = new QPushButton("Fermer");
  main_layout->addWidget(button_close);

  setLayout(main_layout);
  
  connect(button_close, SIGNAL(clicked()), this, SLOT(accept()));

  line_edit->setFocus();
}

void CmdWindow::exec_cmd() {
  std::string cmd = (line_edit->text()).toStdString();
  Cmd::exec(cmd.c_str());
  std::string res = Cmd::get_res();
  text_edit->append(QString(res.c_str()));
  lst_cmd.push_back(line_edit->text());
  pos = lst_cmd.size();
}

void CmdWindow::keyPressEvent(QKeyEvent *event) {
  switch(event->key()) {
  case Qt::Key_Return:
    exec_cmd();
    line_edit->clear();
    break;
  case Qt::Key_Up:
    line_edit->setText(get_prev_cmd());
    break;
  case Qt::Key_Down:
    line_edit->setText(get_next_cmd());
    break;
  }
}

QString CmdWindow::get_prev_cmd() {
  if(lst_cmd.size() > 0) {
    if((pos - 1) >= 0) {
      return lst_cmd[--pos];
    } else {
      return line_edit->text();
    }
  } else {
    return line_edit->text();
  }
}

QString CmdWindow::get_next_cmd() {
  if(lst_cmd.size() > 0) {
    if((pos + 1) < lst_cmd.size()) {
      return lst_cmd[++pos];
    } else {
      return "";
    }
  } else {
    return "";
  }
}
