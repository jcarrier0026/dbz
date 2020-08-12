#include <string>
#include <vector>

#include "location.h"

enum class AnimationType { kDefault, kRunRight, kRunLeft };

// A wrapper struct holding all the info we need about an animation.
struct Animation {
  AnimationType type;
  int time_between_frames_ms;

  // Series of images for animation.
  std::vector<SDL_Rect> image_rects;
  int priority;
};
