#ifndef _CMD
#define _CMD

/* Classe permettant d'executer une commande
 * Le résultat est enregistré dans un programme dont le contenu est récupérable
 */

#include <cstdlib>
#include <string>
#include <fstream>

class Cmd {
public:
  /** 
   * \brief Execute la commande passée en param et redirige
   *   le résultat dans un fichier res_cmd
   * \param cmd est une chaine de caractère représentant la commande
   */
  static void exec(const char * cmd) {
    std::string c = cmd;
    c += " > res_cmd";
    system(c.c_str());
  }

  /**
   * \brief Retourne le contenu du fichier res_cmd
   */
  static std::string get_res() {
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
};

#endif
