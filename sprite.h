#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>

class Sprite {
 public:
  // Ctor takes the sprite sheet file name that this sprite comes from.
  // Additionally, it takes a SpriteLocation indicating the location on the
  // sheet that the sprite should be pulled from.
  Sprite(std::string sprite_sheet_name_, SDL_Rect location);
  virtual ~Sprite() = default;

  virtual SDL_Surface* GetSpriteSheet() const {
    return sprite_sheets_[sprite_sheet_name_];
  }

  virtual SDL_Rect GetSourceLocation() const { return source_location_; }

 private:
  // Sprite sheets. Key is the sheet file name minus extension.
  static std::unordered_map<std::string, SDL_Surface*> sprite_sheets_;

  // Keep track of the sprite sheet this sprite is from.
  const std::string sprite_sheet_name_;

  // The location on the sprite sheet of the desired sprite.
  const SDL_Rect source_location_;
};

#endif /* SPRITE_H */
