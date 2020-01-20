#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <SDL2/SDL.h>

// Graphics-related constants.
constexpr int kWindowWidth = 640;
constexpr int kWindowHeight = 480;
constexpr char kGameTitle[] = "DBZ";

// Structure to hold the RGB values of the background color.
constexpr struct {
  char red = 0x0;
  char green = 0x0;
  char blue = 0xFF;
  char alpha = 0XFF;

} BackgroundColor;

class Graphics {
 public:
  Graphics();
  ~Graphics();
  // Attempts to create the game window.
  void CreateWindow();
  // Call this after contructing a Graphics object to check if initialization
  // succeeded.
  bool InitSuccess() { return window_created_; }

 private:
  bool window_created_ = false;
  SDL_Window* window_;
  SDL_Renderer* renderer_;

  // Function to initialize the SDL library.
  // Returns true if initialization succeeded.
  bool InitSdl();
};

#endif  // GRAPHICS_H
