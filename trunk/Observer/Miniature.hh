#ifndef _MINIATURE
#define _MINIATURE

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>

#include "StationWindow.hh"

class Miniature : public QWidget {

public:
  Miniature(const char * file); //constructeur de test
  Miniature(const char * file, const char * post, const char * user);

private:

  void mouseReleaseEvent(QMouseEvent * e);

  QVBoxLayout * main_layout;
  QLabel * m_img;
  QLabel * m_station_label;
  QLabel * m_user_label;

  QString m_station;
  QString m_user;

};

#endif
