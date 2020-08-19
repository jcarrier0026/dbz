#include "animation_data.h"
#include "animation_frame.h"
#include "location.h"

namespace {
// Animation source rectangles.
constexpr SDL_Rect kGokuIdleStart = {0, 0, 30, 46};
constexpr SDL_Rect kGokuRunRightStart = {60, 0, 32, 46};
constexpr SDL_Rect kGokuRunLeftStart = {60, 46, 32, 46};
constexpr SDL_Rect kSsGokuIdleStart = {0, 92, 28, 46};
constexpr SDL_Rect kSsGokuRunRightStart = {56, 92, 32, 46};
constexpr SDL_Rect kSsGokuRunLeftStart = {56, 138, 32, 46};
constexpr SDL_Rect kGokuSsTransformationStart = {0, 274, 88, 101};

// Take a starting rectangle and number of frames, and build the set of
// rectangles for the given animation.
std::vector<AnimationFrame> BuildAnimationRects(SDL_Rect start,
                                                int number_of_frames) {
  std::vector<AnimationFrame> result;
  int rectangle_width = start.w;
  for (int i = 0; i < number_of_frames; i++) {
    // Move each rectangle x coordinate by the width of the rectangles.
    AnimationFrame frame;
    SDL_Rect rect = start;
    rect.x += i * rectangle_width;
    frame.source = rect;
    frame.offset = {0, 0};
    result.push_back(frame);
  }

  return result;
}

std::vector<AnimationFrame> BuildAnimationRects(SDL_Rect start,
                                                std::vector<Location> offsets) {
  std::vector<AnimationFrame> result;
  int rectangle_width = start.w;
  for (int i = 0; i < static_cast<int>(offsets.size()); i++) {
    // Move each rectangle x coordinate by the width of the rectangles.
    AnimationFrame frame;
    SDL_Rect rect = start;
    rect.x += i * rectangle_width;
    frame.source = rect;
    frame.offset = offsets[i];
    result.push_back(frame);
  }

  return result;
}
}  // namespace

AnimationMap GetGokuAnimations() {
  return {{AnimationType::kDefault,
           {.type = AnimationType::kDefault,
            .time_between_frames_ms = 300,
            .animation_frames =
                BuildAnimationRects(kGokuIdleStart, /*number_of_frames=*/2),
            .priority = 0}},
          {AnimationType::kRunRight,
           {.type = AnimationType::kRunRight,
            .time_between_frames_ms = 100,
            .animation_frames =
                BuildAnimationRects(kGokuRunRightStart, /*number_of_frames=*/2),
            .priority = 1}},
          {AnimationType::kRunLeft,
           {.type = AnimationType::kRunLeft,
            .time_between_frames_ms = 100,
            .animation_frames =
                BuildAnimationRects(kGokuRunLeftStart, /*number_of_frames=*/2),
            .priority = 1}},
          {AnimationType::kSsIdle,
           {.type = AnimationType::kSsIdle,
            .time_between_frames_ms = 300,
            .animation_frames =
                BuildAnimationRects(kSsGokuIdleStart, /*number_of_frames=*/2),
            .priority = 0}},
          {AnimationType::kSsRunRight,
           {.type = AnimationType::kSsRunRight,
            .time_between_frames_ms = 100,
            .animation_frames = BuildAnimationRects(kSsGokuRunRightStart,
                                                    /*number_of_frames=*/2),
            .priority = 1}},
          {AnimationType::kSsRunLeft,
           {.type = AnimationType::kSsRunLeft,
            .time_between_frames_ms = 100,
            .animation_frames = BuildAnimationRects(kSsGokuRunLeftStart,
                                                    /*number_of_frames=*/2),
            .priority = 1}},

          {AnimationType::kSsTransformation,
           {.type = AnimationType::kSsTransformation,
            .time_between_frames_ms = 100,
            .animation_frames = BuildAnimationRects(
                kGokuSsTransformationStart, /*frame_offsets=*/{{-29, -55},
                                                               {-30, -55},
                                                               {-29, -55},
                                                               {-29, -55},
                                                               {-29, -55},
                                                               {-29, -55},
                                                               {-29, -55},
                                                               {-29, -55},
                                                               {-29, -55}}),
            .priority = 2}}};
}
