#include "ScreenShot.hh"

#include <iostream>
using namespace std;

ScreenShot::ScreenShot() : m_surf(NULL), m_pixels(NULL) {
  shot();
}
ScreenShot::ScreenShot(const char * file) : m_surf(NULL), m_pixels(NULL) {
  shot();
  save(file);
}
ScreenShot::~ScreenShot() {
  if(m_surf) {
    SDL_FreeSurface(m_surf);
  }
  if(m_pixels) {
    delete[] m_pixels;
  }	       
}

void ScreenShot::shot() {

  if(m_pixels != NULL)
    delete[] m_pixels;

  Display * display = NULL;
  Window win;
  XWindowAttributes attrib;
  XImage * img = NULL;
  
  display = XOpenDisplay(NULL);
  win     = XDefaultRootWindow(display);
  
  XGetWindowAttributes(display, win, &attrib);
  img = XGetImage(display, win, attrib.x, attrib.y, attrib.width, attrib.height, XAllPlanes(), ZPixmap);

  m_dimx = attrib.width;
  m_dimy = attrib.height;

  m_pixels = new unsigned long[m_dimx*m_dimy];

  for(int x = 0; x < m_dimx; x++) {
    for(int y = 0; y < m_dimy; y++) {
      m_pixels[x + y * m_dimx] = XGetPixel(img, x, y);
    }
  }

  XCloseDisplay(display);
}

SDL_Surface * ScreenShot::get_sdl_surf() {
  return m_surf;
}

bool ScreenShot::save(const char * file) {
  create_surface();

  if(m_surf) {
    SDL_SaveBMP(m_surf, file);
    return true;
  } else {
    return false;
  }
}

bool ScreenShot::save(const char * file, const double zoom) {
  create_surface();

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

void ScreenShot::get_stringstream(const char * file, std::stringstream & ss, int &w, int &h, double zoom) {
  w = m_dimx*zoom;
  h = m_dimy*zoom;
  cout << "dimx = " << h << " dimy = " << w << " prod = " <<  w*h << endl;
  for(int i = 0; i < h*w; i++) {
    ss << m_pixels[i] << " ";
  }
}

void ScreenShot::create_surface() {
  if(m_surf) {
    SDL_FreeSurface(m_surf);
    m_surf = NULL;
  }

  m_surf = SDL_CreateRGBSurface(SDL_HWSURFACE, m_dimx, m_dimy, 32, 0, 0, 0, 0);
  SDL_LockSurface(m_surf);

  for(int x = 0; x < m_dimx; x++) {
    for(int y = 0; y < m_dimy; y++) {
      ((unsigned int *)m_surf->pixels)[x + y * m_dimx] = m_pixels[x + y * m_dimx];
    }
  }

  SDL_UnlockSurface(m_surf);
}
