#include "animated_sprite.h"

#include <iostream>
#include <vector>

#include "constants.h"

AnimatedSprite::AnimatedSprite(const std::string& sprite_sheet_name,
                               SDL_Renderer* renderer, float scale,
                               AnimationMap animations)
    : Sprite(sprite_sheet_name, {}, scale, renderer),
      animations_(std::move(animations)) {}

bool AnimatedSprite::IsItTimeToMoveToNextFrame() {
  SetElapsedTimeMs(SDL_GetTicks());
  if (elapsed_time_ms_ >=
      animations_.at(current_animation_type_).time_between_frames_ms) {
    return true;
  }
  return false;
}

AnimationFrame AnimatedSprite::GetSourceAnimationFrame() const {
  return animations_.at(current_animation_type_).animation_frames[frame_index_];
}

void AnimatedSprite::SetElapsedTimeMs(int time_ms) {
  elapsed_time_ms_ += time_ms - last_time_ms_;
  last_time_ms_ = time_ms;
}

void AnimatedSprite::ChangeAnimation(AnimationType animation, bool once) {
  animation_once_ = once;
  current_animation_type_ = animation;
  frame_index_ = 0;
  elapsed_time_ms_ = 0;
}

void AnimatedSprite::PlayAnimation(AnimationType animation, bool once) {
  // If the animation trying to be played has a higher priority than the current
  // animation.
  const Animation& current = animations_.at(current_animation_type_);
  if (animations_.at(animation).priority > current.priority) {
    ChangeAnimation(animation, once);
  } else if (IsItTimeToMoveToNextFrame()) {
    // If a new animation is trying to play and the current animation has just
    // finished.
    if (current_animation_type_ != animation &&
        frame_index_ == static_cast<int>(current.animation_frames.size()) - 1) {
      ChangeAnimation(animation, once);
    } else {
      frame_index_ = (frame_index_ + 1) %
                     static_cast<int>(current.animation_frames.size());
      elapsed_time_ms_ = 0;
    }
  }
}
