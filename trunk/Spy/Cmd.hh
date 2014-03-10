#ifndef _CMD
#define _CMD

/* Classe permettant d'executer une commande
 * Le résultat est enregistré dans un programme dont le contenu est récupérable
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>

class Cmd {
public:
  Cmd() {
    m_path = ".\n";

    system("pwd > path");
    m_init_path = get_path();
  }

  /** 
   * \brief Execute la commande passée en param et redirige
   *   le résultat dans un fichier res_cmd
   * \param cmd est une chaine de caractère représentant la commande
   */
  void exec(const char * cmd) {
    std::stringstream ss;
    std::string c = cmd;

    /* Si la commande cd a été demandée, on met à jour le path */
    if(c.find("cd") != std::string::npos) {
      ss << "cd " << m_path << " ; " << cmd << " ; pwd > " << m_init_path << "/path";
      system(ss.str().c_str());
      m_path = get_path();
    } else {
      ss << "cd " << m_path << " ; " << cmd << " > " << m_init_path << "/res_cmd";
      system(ss.str().c_str());
    }
  }

  /**
   * \brief Retourne le contenu du fichier res_cmd
   */
  std::string get_res() {
    std::ifstream file("res_cmd");
    std::string res = "";
    if(file) {
      std::string line;
      while(getline(file, line)) {
	res += line;
	res += "\n";
      }
    }
    return res;
  }

  std::string get_path() {
    std::ifstream file("path");
    std::string res = "";
    if(file) {
      std::string line;
      while(getline(file, line)) {
	res += line;
	//res += "\n";
      }
    }
    return res;
 
  }

private:
  std::string m_path;
  std::string m_init_path;
};

#endif
