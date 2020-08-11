#include <string>
#include <vector>

#include "vector2.h"

enum class AnimationType { kIdle, kRunRight, kRunLeft };

struct Animation {
  AnimationType name;
  SDL_Rect source_rect;
  int time_between_frames_ms;
  std::vector<SDL_Rect> image_rects;
  Vector2 offsets;
  int priority;
};

