#include "Spy.hh"

using namespace std;

Spy::Spy() {
  m_user = NULL;
  m_user = getlogin();//need unistd.h (POSIX) / Sinon voir getenv("HOME")

  if(m_user) {
    MsgBox::info(m_user);
  } else {
    MsgBox::warning("Erreur getlogin()");
  }
}

Spy::~Spy() {}
