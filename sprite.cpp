#include "sprite.h"

#include <SDL2/SDL_image.h>

#include <iostream>
#include <sstream>

constexpr char kAssetPath[] = "assets/";

Sprite::Sprite(std::string sprite_sheet_name, SDL_Rect location)
    : sprite_sheet_name_(sprite_sheet_name), source_location_(location) {
  // Check if we've already opened this sprite sheet.
  if (Sprite::sprite_sheets_.find(sprite_sheet_name) != sprite_sheets_.end()) {
    std::stringstream file_path;
    file_path << kAssetPath << sprite_sheet_name << ".png";
    // If the file has never been opened, open it an cache the result.
    SDL_Surface* surface = IMG_Load(file_path.str().c_str());
    if (!surface) {
      std::cout << "Couldn't load image " << sprite_sheet_name
                << ". Error: " << IMG_GetError();
    }
    sprite_sheets_[sprite_sheet_name] = surface;
  }
}

std::unordered_map<std::string, SDL_Surface*> Sprite::sprite_sheets_ =
    std::unordered_map<std::string, SDL_Surface*>();
