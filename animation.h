#include <string>
#include <vector>

#include "vector2.h"

enum class AnimationType { kIdle, kRunRight, kRunLeft };

struct Animation {
  AnimationType name;
  int num_of_frames;
  SDL_Rect source_rect;
  int time_between_frames;
  std::vector<SDL_Rect> image_rects;
  std::string sprite_sheet_name;
  bool once;
  SDL_Renderer *renderer;
  Vector2 offsets;
  int priority;

  Animation &operator=(Animation new_animation);
};

