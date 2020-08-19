#include <string>
#include <vector>

#include "animation_frame.h"
#include "location.h"

enum class AnimationType {
  kDefault,
  kRunRight,
  kRunLeft,
  kSsTransformation,
  kSsIdle,
  kSsRunRight,
  kSsRunLeft
};

// A wrapper struct holding all the info we need about an animation.
struct Animation {
  AnimationType type;
  int time_between_frames_ms;

  // Series of images for animation and their offsets.
  std::vector<AnimationFrame> animation_frames;
  int priority;
};
