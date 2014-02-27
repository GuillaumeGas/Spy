#include "Process.hh"

using namespace std;

Process::Process() {
  refresh();
}

map<int, string> Process::get_list_process() {
  return m_lst_proc;
}

void Process::refresh() {
  DIR * dir_proc = NULL;
  dir_proc = opendir("/proc/");

  if(dir_proc == NULL) {
    cout << "Erreur lors de l'ouverture du dossier." << endl;
    exit(1);
  }

  struct dirent * curr_dir = NULL;
  struct stat    stat_dir; 

  while((curr_dir = readdir(dir_proc)) != NULL) {
    string path = "/proc/";
    path += curr_dir->d_name;
    if(stat(path.c_str(), &stat_dir) != -1) {
      if(S_ISDIR(stat_dir.st_mode) && is_pid(curr_dir->d_name)) {

	DIR * dir_pid = NULL;
	dir_pid = opendir(path.c_str());
	
	if(dir_pid != NULL) {
	  struct dirent * tmp_dir = NULL;
	  while((tmp_dir = readdir(dir_pid)) != NULL) {
	    if(strcmp(tmp_dir->d_name, "cmdline") == 0) {
	      string path_cmdline = path + "/cmdline";
	      string res = get_proc_name_from_cmdfile(path_cmdline);
	      if(res.length() >= 1 && res != " ") {
		m_lst_proc[atoi(curr_dir->d_name)] = res;
	      }
	    }
	  }
	} else {
	  perror("opendir()");
	}
      }
    } else {
      perror(path.c_str());
    }
  }

  if(closedir(dir_proc) == -1) {
    cout << "Erreur lors de la fermeture du dossier." << endl;
    exit(1);
  }
}

void Process::show_list_process() {
  cout << " - PID -  - PROCESSUS - " << endl;
  for(auto it = m_lst_proc.begin(); it != m_lst_proc.end(); it++) {
    cout << it->first << " -- " << it->second << endl;
  }
}

bool Process::process_is_running(string proc_name)const {
  for(auto it = m_lst_proc.begin(); it != m_lst_proc.end(); it++) {
    if(it->second == proc_name) {
      return true;
    }
  }
  return false;
}

int Process::get_proc_pid(string proc_name)const {
  for(auto it = m_lst_proc.begin(); it != m_lst_proc.end(); it++) {
    if(it->second == proc_name) {
      return it->first;
    }
  }
  return -1;
}

string Process::get_proc_name(int proc_id)const {
  auto name = m_lst_proc.find(proc_id);
  if(name == m_lst_proc.end()) {
    return NULL;
  } else {
    return name->second;
  }
}

string Process::read_file(const string file) {
  ifstream fichier(file);
  string res = "";
  if(fichier) {
    string tmp;
    while(!fichier.eof()) {
      fichier >> tmp;
      res += tmp;
    }
  }
  return res;
}

string Process::get_proc_name_from_cmdfile(const string file) {
  string content_file = read_file(file);
  string delimiter    = "/";

  size_t pos = 0;
  string token;

  while((pos = content_file.find(delimiter)) != string::npos) {
    token = content_file.substr(0, pos);
    content_file.erase(0, pos + 1);
  }

  return token;
}

bool Process::is_pid(char * s) {
  for(int i = 0; s[i] != '\0'; i++) {
    if(s[i] < '0' && s[i] > '9') {
      return false;
    }
  }
  return true;
}
