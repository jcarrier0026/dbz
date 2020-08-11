#include "animated_sprite.h"
#include <iostream>
#include "constants.h"

AnimatedSprite::AnimatedSprite(std::string sprite_sheet_name,
                               SDL_Rect first_sprite_coord_location,
                               SDL_Renderer* renderer, SDL_Rect destination)
    : Sprite(sprite_sheet_name, first_sprite_coord_location, renderer),
      current_animation_(AnimationType::kIdle),
      frame_index_(0),
      destination_(destination) {
  SetupAnimations();
}

bool AnimatedSprite::IsItTimeToMoveToNextFrame() {
  SetElapsedTimeMs(SDL_GetTicks());
  if (elapsed_time_ms_ >=
      animations_[current_animation_].time_between_frames_ms) {
    return true;
  }
  return false;
}

SDL_Rect AnimatedSprite::GetDestinationRect() {
  destination_.x =
      (destination_.x + animations_[current_animation_].offsets.x) %
      (constants::kWindowWidth - 64);
  destination_.y += animations_[current_animation_].offsets.y;
  return destination_;
}

SDL_Rect AnimatedSprite::GetCurrentFrameRect() {
  return animations_[current_animation_].image_rects[frame_index_];
}

void AnimatedSprite::SetDestinationRect(const SDL_Rect& new_rect) {
  destination_ = new_rect;
}

void AnimatedSprite::SetElapsedTimeMs(int time_ms) {
  elapsed_time_ms_ += time_ms - last_time_ms_;
  last_time_ms_ = time_ms;
}

void AnimatedSprite::AddAnimation(Animation animation, int num_of_frames) {
  std::vector<SDL_Rect> rectangles;
  SDL_Rect new_rect;
  for (int i = 0; i < num_of_frames; i++) {
    // new_rect is updated with the source rectangle of the next frame of the
    // animation.
    new_rect = animation.source_rect;
    new_rect.x += (i * animation.source_rect.w);
    rectangles.push_back(new_rect);
  }
  animation.image_rects = rectangles;
  animations_.insert(
      std::pair<AnimationType, Animation>(animation.name, animation));
}

void AnimatedSprite::ChangeAnimation(AnimationType animation, bool once) {
  animation_once_ = once;
  current_animation_ = animation;
  frame_index_ = 0;
  elapsed_time_ms_ = 0;
}

void AnimatedSprite::PlayAnimation(AnimationType animation, Perf* perf,
                                   bool once) {
  // If the animation trying to be played has a higher priority than the current
  // animation.
  if (animations_[animation].priority >
      animations_[current_animation_].priority) {
    ChangeAnimation(animation, once);
  } else if (IsItTimeToMoveToNextFrame()) {
    // If a new animation is trying to play and the current animation has just
    // finished.
    if (current_animation_ != animation &&
        frame_index_ ==
            static_cast<int>(
                animations_[current_animation_].image_rects.size() - 1)) {
      ChangeAnimation(animation, once);
    } else {
      frame_index_ =
          (frame_index_ + 1) %
          static_cast<int>(animations_[current_animation_].image_rects.size());
      elapsed_time_ms_ = 0;
    }
  }
}

void AnimatedSprite::SetupAnimations() {
  std::vector<SDL_Rect> rect;
  SDL_Rect source_rectangle = {0, 0, 30, 45};
  int time_between_frames_ms = 300;
  int num_of_frames = 2;
  int priority = 0;

  AddAnimation({AnimationType::kIdle, source_rectangle, time_between_frames_ms,
                rect, Vector2(0, 0), priority},
               num_of_frames);

  source_rectangle = {60, 0, 32, 45};
  time_between_frames_ms = 100;
  num_of_frames = 2;
  priority = 1;

  AddAnimation({AnimationType::kRunRight, source_rectangle,
                time_between_frames_ms, rect, Vector2(4, 0), priority},
               num_of_frames);

  source_rectangle = {60, 46, 32, 45};
  time_between_frames_ms = 100;
  num_of_frames = 2;
  priority = 1;

  AddAnimation({AnimationType::kRunLeft, source_rectangle,
                time_between_frames_ms, rect, Vector2(-4, 0), priority},
               num_of_frames);
}
