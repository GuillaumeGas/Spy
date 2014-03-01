#include <QApplication>
#include "Observer.hh"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  
  Observer obs;
  obs.show();
  
  return app.exec();
}
