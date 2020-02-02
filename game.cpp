#include "game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include "constants.h"

Game::Game() {}

Game::~Game() {}

bool Game::Run() {
  if (!InitSdl()) {
    return false;
  }

  // Initialize the game window.
  graphics_.CreateWindow();

  // Event struct to grab input events from SDL.
  SDL_Event event;

  // DELETE THIS EVENTUALLY
  int goku_location = 0;

  // The game loop.
  while (true) {
    // Clear out old keyup/keydown events.
    input_.BeginNewFrame();

    if (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          return true;
          break;
        case SDL_KEYDOWN:
          if (event.key.repeat == 0) {
            input_.KeyDownEvent(event);
          }
          break;
        case SDL_KEYUP:
          input_.KeyUpEvent(event);
          break;
        default:
          // do nothing
          break;
      }
    }
    if (input_.WasKeyPressed(SDL_SCANCODE_ESCAPE)) {
      return true;
    }

    if (input_.WasKeyPressed(SDL_SCANCODE_B)) {
      graphics_.ChangeWindowColor();
    }

    if (input_.WasKeyPressed(SDL_SCANCODE_D) ||
        input_.IsKeyHeld(SDL_SCANCODE_D)) {
      goku_location += 4;
    }

    Sprite sprite("dbz_character_sprites", {.x = 0, .y = 86, .w = 32, .h = 40});
    SDL_Rect destination = {.x = goku_location % (constants::kWindowWidth - 64),
                            .y = 30,
                            .w = 64,
                            .h = 80};
    graphics_.AddSprite(sprite, destination);

    // TODO: Update the frame here.
    graphics_.DrawNextFrame();
  }
}

bool Game::InitSdl() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "SDL Failed to initialize. Error: " << SDL_GetError()
              << std::endl;
    return false;
  }
  IMG_Init(IMG_INIT_PNG);
  return true;
}
