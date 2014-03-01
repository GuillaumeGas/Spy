#ifndef _SPY
#define _SPY

/**
 * Classe fonctionnant sous forme de service sur un poste
 * Réalise frequemment des captures d'écran et surveille les processus en cours
 * Execute les requêtes envoyées par l'observateur
 *
 */

#include <iostream>
#include <unistd.h>

//#include "Process.hh"
//#include "ScreenShot.hh"
#include "MsgBox.hh"
//#include "Cmd.hh"

class Spy {

public:
  Spy();
  ~Spy();

private:
  char * m_user;

};

#endif
