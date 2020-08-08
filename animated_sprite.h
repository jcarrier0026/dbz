#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "sprite.h"
#include "vector2.h"

class AnimatedSprite : public Sprite {
 public:
  // Constructor takes the name of the sprite sheet, the source rectangle for
  // the first frame, the renderer, and the time between each frame.
  AnimatedSprite(std::string sprite_sheet_name,
                 SDL_Rect first_sprite_coord_location, SDL_Renderer* renderer,
                 float time_to_update_sprite, SDL_Rect destination);

  // Destructor.
  virtual ~AnimatedSprite() = default;
  // Checks to see if it is time to move to the next frame in the current
  // animation.
  void TimeToUpdateFrame();

  // Gets current_animation.
  std::string GetCurrentAnimation();

  // Gets destination_rect_.
  SDL_Rect GetDestinationRect();

  // Gets frame_index_.
  int GetFrameIndex();

  // Gets offsets.
  Vector2 GetOffsets(std::string animation);

  // Gets source rectangle.
  SDL_Rect GetSourceRect(std::string animation, int frame);

  // Gets visible_.
  bool GetVisible();

  // Sets current_animation.
  void SetCurrentAnimation(std::string name);

  // Sets current_animation_once.
  void SetCurrentAnimationOnce(bool once);

  // Sets the destination_rect_.
  void SetDestinationRect(SDL_Rect new_rect);

  // Sets frame_index_.
  void SetFrameIndex(int frame);

  // Sets elapsed_time_.
  void SetElapsedTime(int time);

  // Sets the visible_ variable.
  void SetVisible(bool visible);

 protected:
  double time_to_update;
  bool current_animation_once;
  std::string current_animation;

  // Adds an animations to the map animations_ for this AnimatedSprite.
  void AddAnimation(std::string name, int frames,
                    SDL_Rect first_sprite_coord_location, Vector2 offset);

  // Clears the animations_ map and the offsets_ map.
  void ResetAnimation();

  // Calls the AddAnimation function for all animations.
  virtual void SetupAnimations();

 private:
  // Holds animation name and a vector with all frames for an animation.
  std::unordered_map<std::string, std::vector<SDL_Rect>> animations_;
  // Holds the x and y offsets for each animation.
  std::unordered_map<std::string, Vector2> offsets_;
  // Tells you what frame of an animation you are on.
  int frame_index_;
  // Tells you if the animation is visible or not.
  bool visible_;
  // Tells you how much time has passed since the start of a frame.
  int elapsed_time_ = 0;
  // Tells you when the current frame started.
  int last_time_ = 0;
  // Where the sprite is going on the screen.
  SDL_Rect destination_;
};

#endif  // ANIMATEDSPRITE_H
