#ifndef _MSGBOX
#define _MSGBOX

/**
 * Permet d'afficher des messages de plusieurs sortes (info, attention...)
 * Utilise la commande zenity (se renseigner sur xmessage, libX11..)
 */

#include <cstdlib> //system()
#include <iostream>

class MsgBox {
public:
  static void info(const char * msg) {
    std::string cmd = "zenity --info --text=\"";
    cmd += msg;
    cmd += "\"";
    system(cmd.c_str());
  }
  static void warning(const char * msg) {
    std::string cmd = "zenity --warning --text=\"";
    cmd += msg;
    cmd += "\"";
    system(cmd.c_str());
  }
};

#endif
