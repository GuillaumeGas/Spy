#include <iostream>
#include "Process.hh"
#include "ScreenShot.hh"
#include "MsgBox.hh"
#include "Cmd.hh"
using namespace std;

int main() {
  /*Process proc;
  proc.show_list_process();

  string s = "";
  while(s != "quit") {
    cout << "recherche : ";
    cin >> s;
    if(proc.process_is_running(s)) {
      cout << "pid : " << proc.get_proc_pid(s) << endl;
    } else {
      cout << "none" << endl;
    }
    proc.refresh();
    }*/

  //ScreenShot sc("test.bmp");
  
  //MsgBox::info("l'info du jour!");
  //MsgBox::warning("C'est pas bien du tout");

  Cmd::exec("ls");
  cout << Cmd::get_res() << endl;

  return 0;
}
