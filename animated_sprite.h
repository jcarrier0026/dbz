#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>

#include "animation.h"
#include "perf.h"
#include "sprite.h"
#include "vector2.h"

class AnimatedSprite : public Sprite {
 public:
  // Constructor takes the name of the sprite sheet, the source rectangle for
  // the first frame, the renderer, and the time between each frame.
  AnimatedSprite(std::string sprite_sheet_name,
                 SDL_Rect first_sprite_coord_location, SDL_Renderer* renderer,
                 SDL_Rect destination);

  // Destructor.
  virtual ~AnimatedSprite() = default;

  // Checks to see if it is time to move to the next frame in the current
  // animation.
  bool IsItTimeToMoveToNextFrame();

  // Gets destination_rect_.
  SDL_Rect GetDestinationRect();

  // Gets destination_rect_.
  SDL_Rect GetCurrentFrameRect();

  // Sets the destination_rect_.
  void SetDestinationRect(const SDL_Rect& new_rect);

  // Updates the current animation and the elapsed time since the
  // start of the current frame.
  void PlayAnimation(AnimationType animation, Perf* perf, bool once);

 private:
  // Keeps track of what animation is playing.
  AnimationType current_animation_;

  // Keeps track of which frame of the animation is currently on screen.
  int frame_index_;
  // Tells you how much time has passed since the start of a frame.
  int elapsed_time_ms_ = 0;
  // Tells you when the current frame started.
  int last_time_ms_ = 0;
  // Where the sprite is going to be print on the screen.
  SDL_Rect destination_;
  // Tells you if the current animation should only play once.
  bool animation_once_;

  // This is a map of all animations.
  std::unordered_map<AnimationType, Animation> animations_;

  // Sets elapsed_time_.
  void SetElapsedTimeMs(int time_ms);

  // Adds an animations to the map animations_ for this AnimatedSprite.
  void AddAnimation(Animation animation, int num_of_frames);

  // Change the current animation.
  void ChangeAnimation(AnimationType, bool once);

  // Calls the AddAnimation function for all animations.
  virtual void SetupAnimations();
};

#endif  // ANIMATEDSPRITE_H
