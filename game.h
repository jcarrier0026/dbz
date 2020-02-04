#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "input.h"

// The top-level class that controls the game loop.
// This class starts the game and orchestrates it.
class Game {
 public:
  Game();
  virtual ~Game();

  // Start the game.
  // This function does not return because the game loop is inside.
  bool Run();

 private:
  // Function to initialize the SDL library.
  // Returns true if initialization succeeded.
  bool InitSdl();

  // Limits the frame rate.
  void LimitFrameRate();

  // Controls all graphics-related functionality.
  Graphics graphics_;

  // Keeps track of when the current frame started.
  int frame_start_time_ms;

  // Controls all input-related functionality.
  Input input_;
};

#endif /* GAME_H */
