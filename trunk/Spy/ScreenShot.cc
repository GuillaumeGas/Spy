#include "ScreenShot.hh"

ScreenShot::ScreenShot() : m_surf(NULL) {
  shot();
}
ScreenShot::ScreenShot(const char * file) : m_surf(NULL) {
  shot();
  save(file);
}
ScreenShot::~ScreenShot() {
  if(m_surf) 
    SDL_FreeSurface(m_surf);
}

void ScreenShot::shot() {
  if(m_surf) {
    SDL_FreeSurface(m_surf);
    m_surf = NULL;
  }

  Display * display = NULL;
  Window win;
  XWindowAttributes attrib;
  XImage * img = NULL;
  
  display = XOpenDisplay(NULL);
  win     = XDefaultRootWindow(display);
  
  XGetWindowAttributes(display, win, &attrib);
  img = XGetImage(display, win, attrib.x, attrib.y, attrib.width, attrib.height, XAllPlanes(), ZPixmap);

  m_surf = SDL_CreateRGBSurface(SDL_HWSURFACE, attrib.width, attrib.height, 32, 0, 0, 0, 0);
  SDL_LockSurface(m_surf);

  for(int x = 0; x < attrib.width; x++) {
    for(int y = 0; y < attrib.height; y++) {
      ((unsigned int *)m_surf->pixels)[x + y * attrib.width] = XGetPixel(img, x, y);
    }
  }

  SDL_UnlockSurface(m_surf);
  XCloseDisplay(display);
}

SDL_Surface * ScreenShot::get_sdl_surf() {
  return m_surf;
}

bool ScreenShot::save(const char * file) {
  if(m_surf) {
    SDL_SaveBMP(m_surf, file);
    return true;
  } else {
    return false;
  }
}

bool ScreenShot::save_miniature(const char * file, const double zoom) {
  if(m_surf) {
    SDL_Surface * surf_mini = rotozoomSurface(m_surf, 0, zoom, 1);
    if(surf_mini) {
      SDL_SaveBMP(surf_mini, file);
      return true;
    } else{
      return false;
    }
  } else {
    return false;
  }
}
