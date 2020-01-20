#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

#include <map>

class Input {
 public:
  void BeginNewFrame();

  void KeyUpEvent(const SDL_Event& event);
  void KeyDownEvent(const SDL_Event& event);

  // The below methods return true if the key is in the specified state.
  bool WasKeyPressed(SDL_Scancode key);
  bool WasKeyReleased(SDL_Scancode key);
  bool IsKeyHeld(SDL_Scancode key);

 private:
  std::map<SDL_Scancode, bool> held_keys_;
  std::map<SDL_Scancode, bool> pressed_keys_;
  std::map<SDL_Scancode, bool> released_keys_;
};

#endif /* INPUT_H */
