#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>

#include <string>
#include <unordered_map>

#include "animation.h"
#include "location.h"
#include "perf.h"
#include "sprite.h"

using AnimationMap = std::unordered_map<AnimationType, Animation>;

class AnimatedSprite : public Sprite {
 public:
  // Construct an animated sprite.
  // Params:
  //   sprite_sheet_name - The name of the sprite sheet.
  //   renderer          - SDL_renderer to use for this sprite.
  //   scale             - Ratio of source rectangle area to destination
  //                       rectangle area.
  //   animations        - The map of animations possible for this sprite.
  AnimatedSprite(const std::string& sprite_sheet_name, SDL_Renderer* renderer,
                 float scale, AnimationMap animations);

  // Destructor.
  virtual ~AnimatedSprite() = default;

  // Checks to see if it is time to move to the next frame in the current
  // animation.
  bool IsItTimeToMoveToNextFrame();

  // Returns the current source location for the animated sprite.
  SDL_Rect GetSourceLocation() const override;

  // Gets the width of the drawn sprite on the screen.
  int GetWidth() const {
    return static_cast<int>(GetSourceLocation().w * scale_);
  }

  // Updates the current animation and the elapsed time since the
  // start of the current frame.
  void PlayAnimation(AnimationType animation, bool once = false);

 private:
  // Keeps track of what animation is playing.
  AnimationType current_animation_type_ = AnimationType::kDefault;

  // Keeps track of which frame of the animation is currently on screen.
  int frame_index_ = 0;

  // Tells you how much time has passed since the start of a frame.
  int elapsed_time_ms_ = 0;

  // Tells you when the current frame started.
  int last_time_ms_ = 0;

  // Tells you if the current animation should only play once.
  bool animation_once_ = false;

  // This is a map of all animations.
  const AnimationMap animations_;

  // Sets elapsed_time_.
  void SetElapsedTimeMs(int time_ms);

  // Change the current animation.
  void ChangeAnimation(AnimationType, bool once);
};

#endif  // ANIMATEDSPRITE_H
