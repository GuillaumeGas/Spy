#ifndef _SCREEN_SHOT
#define _SCREEN_SHOT

/** 
    Classe permettant de réaliser un screen shot à l'aide de la libX11 
    Permet d'en récupérer une surface sdl, ou de l'enregistrer au format bmp

    Flags nécessaires : -lSDL -lX11
*/

#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

class ScreenShot {

public:
  ScreenShot();
  ScreenShot(const char * file);
  ~ScreenShot();

  void shot();
  SDL_Surface * get_sdl_surf();
  bool save(const char * file);
  bool save_miniature(const char * file, const double zoom);

private:
  SDL_Surface * m_surf;

};

#endif
