#include "animated_sprite.h"
#include <iostream>

// Constructor.
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

void AnimatedSprite::TimeToUpdateFrame() {
  //  std::cout << elapsed_time_ << std::endl;
  if (elapsed_time_ >= time_to_update) {
    if (frame_index_ <
        (int)this->animations_[this->current_animation].size() - 1) {
      frame_index_++;
    } else {
      if (current_animation_once == true) {
        this->SetVisible(false);
        this->AnimationDone(this->current_animation);
      }
      frame_index_ = 0;
    }
    elapsed_time_ = 0;
  }
}

SDL_Rect AnimatedSprite::GetDestinationRect() { return destination_; }

void AnimatedSprite::SetDestinationRect(SDL_Rect new_rect) {
  destination_.x = new_rect.x;
  destination_.y = new_rect.y;
  destination_.w = new_rect.w;
  destination_.h = new_rect.h;
}

// Gets source rectangle.
SDL_Rect AnimatedSprite::GetSourceRect(std::string animation, int frame) {
  return this->animations_[animation][frame];
}

// Set current animation.
void AnimatedSprite::SetCurrentAnimation(std::string name) {
  this->current_animation = name;
}

// Get current animation.
std::string AnimatedSprite::GetCurrentAnimation() {
  return this->current_animation;
}

// Get frame index.
int AnimatedSprite::GetFrameIndex() { return this->frame_index_; }

// Set frame index.
void AnimatedSprite::SetFrameIndex(int frame) { this->frame_index_ = frame; }

// Set elapsed time.
void AnimatedSprite::SetElapsedTime(int time) {
  elapsed_time_ += time - last_time_;
  last_time_ = time;
}

void AnimatedSprite::SetCurrentAnimationOnce(bool once) {
  this->current_animation_once = once;
}

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
  this->animations_.insert(
      std::pair<std::string, std::vector<SDL_Rect>>(name, rectangles));
  this->offsets_.insert(std::pair<std::string, Vector2>(name, offset));
}

void AnimatedSprite::ResetAnimation() {
  this->animations_.clear();
  this->offsets_.clear();
}

void AnimatedSprite::StopAnimation() {
  this->frame_index_ = 0;
  this->AnimationDone(this->current_animation);
}

void AnimatedSprite::SetVisible(bool visible) { this->visible_ = visible; }

void AnimatedSprite::AnimationDone(std::string current_animation) {}

Vector2 AnimatedSprite::GetOffsets(std::string animation) {
  return this->offsets_[animation];
}

void AnimatedSprite::SetupAnimations() {
  this->AddAnimation("Idle", 2, {0, 0, 29, 45}, Vector2(0, 0));
  this->AddAnimation("RunRight", 2, {60, 0, 31, 45}, Vector2(4, 0));
}
