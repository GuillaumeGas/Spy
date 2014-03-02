#include "Miniature.hh"

Miniature::Miniature() {
  m_img = new QLabel;
  m_img->setPixmap(QPixmap("img.bmp"));

  m_post = new QLabel("<center><b>info21-01</b></center>");
  m_user = new QLabel("<center><b>Gas</b></center>");

  this->addWidget(m_img);
  this->addWidget(m_post);
  this->addWidget(m_user);
}

Miniature::Miniature(const char * _file, const char * _post, const char * _user) {
  m_img = new QLabel;
  m_img->setPixmap(QPixmap(_file));

  QString post = "<center><b>";
  post += _post;
  post += "</b></center>";
  m_post = new QLabel(post);

  QString user = "<center><b>";
  user += _user;
  user += "</b></center>";
  m_user = new QLabel(user);
}

