#include "input.h"

void Input::BeginNewFrame() {
  pressed_keys_.clear();
  released_keys_.clear();
}

void Input::KeyUpEvent(const SDL_Event& event) {
  released_keys_[event.key.keysym.scancode] = true;
  held_keys_[event.key.keysym.scancode] = false;
}

void Input::KeyDownEvent(const SDL_Event& event) {
  pressed_keys_[event.key.keysym.scancode] = true;
  held_keys_[event.key.keysym.scancode] = true;
}

bool Input::WasKeyPressed(SDL_Scancode key) { return pressed_keys_[key]; }

bool Input::WasKeyReleased(SDL_Scancode key) { return released_keys_[key]; }

bool Input::IsKeyHeld(SDL_Scancode key) { return held_keys_[key]; }
