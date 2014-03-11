#ifndef _MSGBOX
#define _MSGBOX

/**
 * Permet d'afficher des messages de plusieurs sortes (info, attention...)
 * Utilise la commande zenity (se renseigner sur xmessage, libX11..)
 */

#include <cstdlib> //system()
#include <iostream>
#include <sstream>

class MsgBox {
public:
  static void info(const char * msg) {
    std::stringstream cmd;
    cmd << "zenity --info --text=\"";
    cmd << msg;
    cmd << "\"";
    system(cmd.str().c_str());
  }
  static void info(const std::string msg) {
    std::stringstream cmd;
    cmd << "zenity --info --text=\"";
    cmd << msg;
    cmd << "\"";
    system(cmd.str().c_str());
  }
    

  static void warning(const char * msg) {
    std::stringstream cmd;
    cmd << "zenity --warning --text=\"";
    cmd << msg;
    cmd << "\"";
    system(cmd.str().c_str());
  }
  static void warning(const std::string msg) {
    std::stringstream cmd;
    cmd << "zenity --warning --text=\"";
    cmd << msg;
    cmd << "\"";
    system(cmd.str().c_str());
  }
  
  
};

#endif
