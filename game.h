#ifndef GAME_H
#define GAME_H

#include "graphics.h"

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

  // Controls all graphics-related functionality.
  Graphics graphics_;
};

#endif /* GAME_H */
