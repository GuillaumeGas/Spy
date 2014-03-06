#include "Miniature.hh"

Miniature::Miniature(const char * file) {
  m_user = "user_test";
  m_station = "post_test";

  main_layout = new QVBoxLayout;
  
  m_img = new QLabel;
  m_img->setPixmap(QPixmap(file));

  m_station_label = new QLabel("<center><b>info21-01</b></center>");
  m_user_label = new QLabel("<center><b>Gas</b></center>");

  main_layout->addWidget(m_img);
  main_layout->addWidget(m_station_label);
  main_layout->addWidget(m_user_label);

  setLayout(main_layout);
}

Miniature::Miniature(const char * _file, const char * _station, const char * _user) {
  m_station = _station;
  m_user = _user;

  main_layout = new QVBoxLayout;

  m_img = new QLabel;
  m_img->setPixmap(QPixmap(_file));

  QString station = "<center><b>";
  station += _station;
  station += "</b></center>";
  m_station_label = new QLabel(station);

  QString user = "<center><b>";
  user += _user;
  user += "</b></center>";
  m_user_label = new QLabel(user);

  main_layout->addWidget(m_img);
  main_layout->addWidget(m_station_label);
  main_layout->addWidget(m_user_label);

  setLayout(main_layout);
  setStyleSheet("QWidget:hover{background-color: #808080;}");
}

void Miniature::mouseReleaseEvent(QMouseEvent * e) {
  StationWindow station_win(m_station, m_user);
  station_win.exec();
}

void Miniature::set_hover_style(QString style) {
  setStyleSheet("QWidget:hover{"+style+"}");
}

void Miniature::set_style(QString style) {
  setStyleSheet("QWidget{"+style+"}");
}
