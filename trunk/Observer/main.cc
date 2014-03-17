#include <QApplication>
#include "Observer.hh"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  
  observer::Observer obs(argc, argv);
  obs.show();
  
  return app.exec();
}

