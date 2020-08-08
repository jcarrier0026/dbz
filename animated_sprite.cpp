#include "animated_sprite.h"
#include <iostream>

// AnimatedSprite()
AnimatedSprite::AnimatedSprite(std::string sprite_sheet_name,
                               SDL_Rect first_sprite_coord_location,
                               SDL_Renderer* renderer,
                               float time_to_update_sprite,
                               SDL_Rect destination)
    : Sprite(sprite_sheet_name, first_sprite_coord_location, renderer),
      time_to_update(time_to_update_sprite),
      current_animation_once(false),
      current_animation(""),
      frame_index_(0),
      visible_(true),
      destination_(destination) {
  this->SetupAnimations();
}

// TimeToUpdateFrame()
void AnimatedSprite::TimeToUpdateFrame() {
  if (elapsed_time_ >= time_to_update) {
    if (frame_index_ < (int)animations_[this->current_animation].size() - 1) {
      frame_index_++;
    } else {
      if (current_animation_once == true) {
        this->SetVisible(false);
      }
      frame_index_ = 0;
    }
    elapsed_time_ = 0;
  }
}

// GetCurrentAnimation()
std::string AnimatedSprite::GetCurrentAnimation() { return current_animation; }

// GetDestinationRect()
SDL_Rect AnimatedSprite::GetDestinationRect() { return destination_; }

// GetFrameIndex()
int AnimatedSprite::GetFrameIndex() { return frame_index_; }

// GetOffsets()
Vector2 AnimatedSprite::GetOffsets(std::string animation) {
  return offsets_[animation];
}

// GetSourceRect()
SDL_Rect AnimatedSprite::GetSourceRect(std::string animation, int frame) {
  return animations_[animation][frame];
}

// GetVisible()
bool AnimatedSprite::GetVisible() { return visible_; }

// SetCurrentAnimation()
void AnimatedSprite::SetCurrentAnimation(std::string name) {
  current_animation = name;
}

// SetCurrentAnimationOnce()
void AnimatedSprite::SetCurrentAnimationOnce(bool once) {
  current_animation_once = once;
}

// SetDestinationRect()
void AnimatedSprite::SetDestinationRect(SDL_Rect new_rect) {
  destination_.x = new_rect.x;
  destination_.y = new_rect.y;
  destination_.w = new_rect.w;
  destination_.h = new_rect.h;
}

// SetElapsedTime()
void AnimatedSprite::SetElapsedTime(int time) {
  elapsed_time_ += time - last_time_;
  last_time_ = time;
}

// SetFrameIndex()
void AnimatedSprite::SetFrameIndex(int frame) { frame_index_ = frame; }

// SetVisible()
void AnimatedSprite::SetVisible(bool visible) { visible_ = visible; }

// AddAnimation()
void AnimatedSprite::AddAnimation(std::string name, int frames,
                                  SDL_Rect first_sprite_coord_location,
                                  Vector2 offset) {
  std::vector<SDL_Rect> rectangles;
  SDL_Rect new_rect;
  for (int i = 0; i < frames; i++) {
    new_rect = first_sprite_coord_location;
    new_rect.x += (i * first_sprite_coord_location.w) + 1;
    rectangles.push_back(new_rect);
  }
  animations_.insert(
      std::pair<std::string, std::vector<SDL_Rect>>(name, rectangles));
  offsets_.insert(std::pair<std::string, Vector2>(name, offset));
}

// ResetAnimation()
void AnimatedSprite::ResetAnimation() {
  animations_.clear();
  offsets_.clear();
}

// SetupAnimations()
void AnimatedSprite::SetupAnimations() {
  AddAnimation("Idle", 2, {0, 0, 29, 45}, Vector2(0, 0));
  AddAnimation("RunRight", 2, {60, 0, 31, 45}, Vector2(4, 0));
}
