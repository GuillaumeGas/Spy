#ifndef _PROCESS
#define _PROCESS

/**
 *  Classe permettant d'avoir des informations sur les processus en cours
 */

#include <iostream>
#include <map>
#include <fstream>
#include <cstdlib>
#include <cstring>

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

class Process {

public:
  Process();
  std::map<int, std::string> get_list_process();
  void refresh();
  void show_list_process();

  bool process_is_running(std::string proc_name)const;
  int  get_proc_pid(std::string proc_name)const;
  std::string get_proc_name(int proc_id)const;

private:
  std::string read_file(const std::string file);
  std::string get_proc_name_from_cmdfile(const std::string file);
  bool is_pid(char * s);
  
  std::map<int, std::string> m_lst_proc;

};

#endif
