#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

#include <string>
#include <unordered_map>
#include "animation_frame.h"
#include "location.h"

class Sprite {
 public:
  // Ctor takes the sprite sheet file name that this sprite comes from.
  // Additionally, it takes a Sprite Location indicating the location on the
  // sheet that the sprite should be pulled from.
  // It also takes a pointer to the renderer in order to make textures.
  // The renderer is not owned by the sprite.

  Sprite(std::string sprite_sheet_name, SDL_Rect location, float scale,
         SDL_Renderer* renderer);

  virtual ~Sprite() = default;

  virtual SDL_Texture* GetSpriteTexture() const {
    return sprite_textures_[sprite_sheet_name_];
  }

  virtual AnimationFrame GetSourceAnimationFrame() const {
    return {source_location_, {0, 0}};
  }

  // Returns the scale.
  virtual float GetScale() const { return scale_; }

  // Cache the texture once the Graphics class makes it for us.
  virtual void CacheTexture(SDL_Texture* texture) {
    sprite_textures_[sprite_sheet_name_] = texture;
  }

 protected:
  // Sprite sheets. Key is the sheet file name minus extension.
  static std::unordered_map<std::string, SDL_Texture*> sprite_textures_;

  // Keep track of the sprite sheet this sprite is from.
  const std::string sprite_sheet_name_;

  // The location on the sprite sheet of the desired sprite.
  const SDL_Rect source_location_;

  // The ratio of source to destination rectangle.
  float scale_ = 1.0f;
};

#endif /* SPRITE_H */
