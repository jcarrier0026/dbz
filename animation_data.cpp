#include "animation_data.h"

namespace {
constexpr SDL_Rect kGokuIdleStart = {0, 0, 30, 45};
constexpr SDL_Rect kGokuRunRightStart = {60, 0, 32, 45};
constexpr SDL_Rect kGokuRunLeftStart = {60, 46, 32, 45};

// Take a starting rectangle and number of frames, and build the set of
// rectangles for the given animation.
std::vector<SDL_Rect> BuildAnimationRects(SDL_Rect start,
                                          int number_of_frames) {
  std::vector<SDL_Rect> result;
  int rectangle_width = start.w;
  for (int i = 0; i < number_of_frames; i++) {
    // Move each rectangle x coordinate by the width of the rectangles.
    SDL_Rect rect = start;
    rect.x += i * rectangle_width;
    result.push_back(rect);
  }

  return result;
}
}  // namespace

AnimationMap GetGokuAnimations() {
  return {{AnimationType::kDefault,
           {.type = AnimationType::kDefault,
            .time_between_frames_ms = 300,
            .image_rects =
                BuildAnimationRects(kGokuIdleStart, /*number_of_frames=*/2),
            .priority = 0}},
          {AnimationType::kRunRight,
           {.type = AnimationType::kRunRight,
            .time_between_frames_ms = 100,
            .image_rects =
                BuildAnimationRects(kGokuRunRightStart, /*number_of_frames=*/2),
            .priority = 1}},
          {AnimationType::kRunLeft,
           {.type = AnimationType::kRunLeft,
            .time_between_frames_ms = 100,
            .image_rects =
                BuildAnimationRects(kGokuRunLeftStart, /*number_of_frames=*/2),
            .priority = 1}}};
}
