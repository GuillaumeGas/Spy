#ifndef _MINIATURE
#define _MINIATURE

#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>

class Miniature : public QVBoxLayout {

public:
  Miniature(); //constructeur de test
  Miniature(const char * file, const char * post, const char * user);

private:
  QLabel * m_img;
  QLabel * m_post;
  QLabel * m_user;

};

#endif
