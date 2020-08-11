#include "animated_sprite.h"
#include <iostream>
#include "constants.h"

AnimatedSprite::AnimatedSprite(std::string sprite_sheet_name,
                               SDL_Rect first_sprite_coord_location,
                               SDL_Renderer* renderer,
                               float time_to_update_sprite,
                               SDL_Rect destination)
    : Sprite(sprite_sheet_name, first_sprite_coord_location, renderer),
      current_animation(AnimationType::kIdle),
      frame_index_(0),
      destination_(destination) {
  animation.time_between_frames = time_to_update_sprite;
  animation.once = false;
  animation.sprite_sheet_name = sprite_sheet_name;
  animation.renderer = renderer;
  this->SetupAnimations();
}

bool AnimatedSprite::TimeToUpdateFrame() {
  // Here
  SetElapsedTime(SDL_GetTicks());
  if (elapsed_time_ >= animations_[current_animation].time_between_frames) {
    return true;
  }
  return false;
}

SDL_Rect AnimatedSprite::GetDestinationRect() {
  destination_.x = (destination_.x + animations_[current_animation].offsets.x) %
                   (constants::kWindowWidth - 64);
  destination_.y += animations_[current_animation].offsets.y;
  return destination_;
}

SDL_Rect AnimatedSprite::GetCurrentFrameRect() {
  return animations_[current_animation].image_rects[frame_index_];
}

void AnimatedSprite::SetDestinationRect(SDL_Rect new_rect) {
  destination_ = new_rect;
}

void AnimatedSprite::SetElapsedTime(int time) {
  elapsed_time_ += time - last_time_;
  last_time_ = time;
}

void AnimatedSprite::AddAnimation() {
  std::vector<SDL_Rect> rectangles;
  SDL_Rect new_rect;
  for (int i = 0; i < animation.num_of_frames; i++) {
    new_rect = animation.source_rect;
    new_rect.x += (i * animation.source_rect.w);
    rectangles.push_back(new_rect);
  }
  animation.image_rects = rectangles;
  animations_.insert(
      std::pair<AnimationType, Animation>(animation.name, animation));
}

void AnimatedSprite::ChangeAnimation(AnimationType animation, bool once) {
  animations_[animation].once = once;
  current_animation = animation;
  frame_index_ = 0;
  elapsed_time_ = 0;
}

void AnimatedSprite::PlayAnimation(AnimationType animation, Perf* perf,
                                   bool once) {
  if (animations_[animation].priority >
      animations_[current_animation].priority) {
    ChangeAnimation(animation, once);
  } else if (TimeToUpdateFrame()) {
    if (current_animation != animation &&
        frame_index_ == animations_[current_animation].num_of_frames - 1) {
      ChangeAnimation(animation, once);
    } else {
      frame_index_ =
          (frame_index_ + 1) % animations_[current_animation].num_of_frames;
      elapsed_time_ = 0;
    }
  }
}

Animation& Animation::operator=(Animation new_animation) {
  name = new_animation.name;
  num_of_frames = new_animation.num_of_frames;
  source_rect = new_animation.source_rect;
  time_between_frames = new_animation.time_between_frames;
  image_rects = new_animation.image_rects;
  sprite_sheet_name = new_animation.sprite_sheet_name;
  once = new_animation.once;
  renderer = new_animation.renderer;
  offsets = new_animation.offsets;
  priority = new_animation.priority;
  return *this;
}

void AnimatedSprite::ResetAnimation() { animations_.clear(); }

void AnimatedSprite::SetupAnimations() {
  std::vector<SDL_Rect> rect;
  SDL_Rect source_rectangle = {0, 0, 30, 45};
  int time_between_frames = 300;
  int num_of_frames = 2;
  int priority = 0;
  bool once = false;

  animation = {AnimationType::kIdle,
               num_of_frames,
               source_rectangle,
               time_between_frames,
               rect,
               animation.sprite_sheet_name,
               once,
               animation.renderer,
               Vector2(0, 0),
               priority};
  AddAnimation();

  source_rectangle = {60, 0, 32, 45};
  time_between_frames = 100;
  num_of_frames = 2;
  priority = 1;
  once = false;

  animation = {AnimationType::kRunRight,
               num_of_frames,
               source_rectangle,
               time_between_frames,
               rect,
               animation.sprite_sheet_name,
               once,
               animation.renderer,
               Vector2(4, 0),
               priority};
  AddAnimation();

  source_rectangle = {60, 46, 32, 45};
  time_between_frames = 100;
  num_of_frames = 2;
  priority = 1;
  once = false;

  animation = {AnimationType::kRunLeft,
               num_of_frames,
               source_rectangle,
               time_between_frames,
               rect,
               animation.sprite_sheet_name,
               once,
               animation.renderer,
               Vector2(-4, 0),
               priority};
  AddAnimation();
}
