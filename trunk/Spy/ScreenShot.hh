#ifndef _SCREEN_SHOT
#define _SCREEN_SHOT

/** 
    Classe permettant de réaliser un screen shot à l'aide de la libX11 
    Permet d'en récupérer une surface sdl, ou de l'enregistrer au format bmp

    Flags nécessaires : -lSDL -lSDL_gfx -lX11
*/

#include <iostream>
#include <sstream>
#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

class ScreenShot {

public:
  /**
   * \brief Fait appel à shot()
   */
  ScreenShot();
  /**
   * \brief fait appel à shot et enregistre l'image au format bmp. Attention taille originale conservée
   * \param file représente le nom du fichier dans lequel sauvegarder l'image
   */
  ScreenShot(const char * file);
  ~ScreenShot();

  /**
   *  \brief Réalise la capture d'écran et la stocke dans une surface
   */
  void shot();
  
  /**
   *  \brief Retourne un pointeur sur la surface comportant l'image du screenshot
   *  \return Pointeur sur une surface. Attention la surface n'existe plus une fois l'objet détruit
   */
  SDL_Surface * get_sdl_surf();

  /**
   *  \brief Sauvegarde l'image dans un fichier bmp
   *  \param save représente le nom du fichier dans lequel enregistrer l'image
   */
  bool save(const char * file);
  
  /**
   *  \brief Sauvegarde l'image dans un fichier bmp
   *  \param save représente le nom du fichier dans lequel enregistrer l'image
   *  \param zoom permet de redimensioner l'image (zoom > 0 et < 1 pour diminution)
   */
  bool save(const char * file, const double zoom);

  void get_stringstream(const char * file, std::stringstream & ss, int &w, int &h, double zoom);

  static void build_bmp_fromStringstream(const char * file, std::stringstream &ss, int width, int height) {
    SDL_Surface * surf = SDL_CreateRGBSurface(SDL_HWSURFACE, width, height, 32, 0, 0, 0, 0);
    SDL_LockSurface(surf);
    int i = 0;
    while(!ss.eof()) {
      int a;
      ss >> a;
      //std::cout << "a = " << a << std::endl;
      ((unsigned int *)surf->pixels)[i++] = a;
      //std::cout << "i = " << i << std::endl;
    }
    SDL_UnlockSurface(surf);

    if(surf) {
      SDL_SaveBMP(surf, file);
    } else {
      std::cout << "Erreur, surface vide." << std::endl;
    }
  }

private:
  void create_surface();

  int m_dimx, m_dimy;
  SDL_Surface * m_surf;
  unsigned long * m_pixels;

};

#endif
