#ifndef ANIMATIONFRAME
#define ANIMATIONFRAME
#include "location.h"

struct AnimationFrame {
  SDL_Rect source;
  Location offset;

  AnimationFrame() : source({}), offset(0, 0) {}
  AnimationFrame(SDL_Rect rect, Location location)
      : source(rect), offset(location) {}
};
#endif
