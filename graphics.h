#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <iostream>


 //constants
 constexpr int kWindowWidth = 640;
 constexpr int kWindowHeight = 480;
 constexpr char kGameTitle[] = "DBZ";

 //holds RGB values of background
 constexpr struct {
  char red = 0x0;
  char green = 0x0;
  char blue = 0xFF;

  //opaque SDL constant
  char alpha = SDL_ALPHA_OPAQUE;

}BackgroundColor;//background colors

class Graphics {
public:
 //initialize SDL library
 bool InitSdl(); 
 int createWindow(); 
};
#endif  // GRAPHICS_H
