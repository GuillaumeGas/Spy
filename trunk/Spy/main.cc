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
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface * ecran = SDL_SetVideoMode(1600, 900, 32, SDL_HWSURFACE);
    SDL_Event e;
    while (1) {
	SDL_PollEvent(&e);
	if ( e.type == SDL_QUIT ) {
	    return 0;
	}
	ScreenShot sc;
	SDL_Rect r = {0,0,0,0};
	SDL_BlitSurface(sc.get_sdl_surf(), NULL, ecran, &r);
	SDL_Flip(ecran);
    }
  
    MsgBox::info("l'info du jour!");
    MsgBox::warning("C'est pas bien du tout");

  Cmd::exec("ls");
  cout << Cmd::get_res() << endl;

  return 0;
}
