#include "animation_data.h"
#include "location.h"

namespace {
constexpr SDL_Rect kGokuIdleStart = {0, 0, 30, 46};
constexpr SDL_Rect kGokuRunRightStart = {60, 0, 32, 46};
constexpr SDL_Rect kGokuRunLeftStart = {60, 46, 32, 46};
constexpr SDL_Rect kSSGokuIdleStart = {0, 92, 28, 46};
constexpr SDL_Rect kSSGokuRunRightStart = {56, 92, 32, 46};
constexpr SDL_Rect kSSGokuRunLeftStart = {56, 138, 32, 46};
constexpr SDL_Rect kGokuSSTransformationStart = {0, 274, 88, 101};

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

// Takes the number of frames and sets the offset for each frame of the
// animation to zero.
std::vector<Location> NoOffsets(int number_of_frames) {
  std::vector<Location> result;
  for (int i = 0; i < number_of_frames; i++) {
    result.push_back({0, 0});
  }

  return result;
}
}  // namespace

AnimationMap GetGokuAnimations() {
  return {{AnimationType::kDefault,
           {.type = AnimationType::kDefault,
            .time_between_frames_ms = 300,
            .offsets = NoOffsets(/*number_of_frames*/ 2),
            .image_rects =
                BuildAnimationRects(kGokuIdleStart, /*number_of_frames=*/2),
            .priority = 0}},
          {AnimationType::kRunRight,
           {.type = AnimationType::kRunRight,
            .time_between_frames_ms = 100,
            .offsets = NoOffsets(/*number_of_frames*/ 2),
            .image_rects =
                BuildAnimationRects(kGokuRunRightStart, /*number_of_frames=*/2),
            .priority = 1}},
          {AnimationType::kRunLeft,
           {.type = AnimationType::kRunLeft,
            .time_between_frames_ms = 100,
            .offsets = NoOffsets(/*number_of_frames=*/2),
            .image_rects =
                BuildAnimationRects(kGokuRunLeftStart, /*number_of_frames=*/2),
            .priority = 1}},
          {AnimationType::kSSIdle,
           {.type = AnimationType::kSSIdle,
            .time_between_frames_ms = 300,
            .offsets = NoOffsets(/*number_of_frames=*/2),
            .image_rects =
                BuildAnimationRects(kSSGokuIdleStart, /*number_of_frames=*/2),
            .priority = 0}},
          {AnimationType::kSSRunRight,
           {.type = AnimationType::kSSRunRight,
            .time_between_frames_ms = 100,
            .offsets = NoOffsets(/*number_of_frames=*/2),
            .image_rects = BuildAnimationRects(kSSGokuRunRightStart,
                                               /*number_of_frames=*/2),
            .priority = 1}},
          {AnimationType::kSSRunLeft,
           {.type = AnimationType::kSSRunLeft,
            .time_between_frames_ms = 100,
            .offsets = NoOffsets(/*number_of_frames=*/2),
            .image_rects = BuildAnimationRects(kSSGokuRunLeftStart,
                                               /*number_of_frames=*/2),
            .priority = 1}},

          {AnimationType::kSSTransformation,
           {.type = AnimationType::kSSTransformation,
            .time_between_frames_ms = 100,
            .offsets = {{-29, -55},
                        {-30, -55},
                        {-29, -55},
                        {-29, -55},
                        {-29, -55},
                        {-29, -55},
                        {-29, -55},
                        {-29, -55},
                        {-29, -55}},
            .image_rects = BuildAnimationRects(kGokuSSTransformationStart,
                                               /*number_of_frames=*/9),
            .priority = 2}}};
}
