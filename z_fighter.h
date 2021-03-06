#ifndef Z_FIGHTER_H
#define Z_FIGHTER_H

#include "animated_sprite.h"
#include "game_object.h"
#include "location.h"
#include "sprite.h"

// The Z Fighter is the hero GameObject. It responds to user input.
class ZFighter : public GameObject {
 public:
  // Provide a starting location and sprite.
  ZFighter(AnimatedSprite sprite, Location location)
      : sprite_(std::move(sprite)), location_(location) {}

  // Return the current location of the object.
  Location GetLocation() const override { return location_; }

  // Return the sprite for the object.
  const Sprite& GetSprite() const override { return sprite_; }

  // Temporary function until we have Physics and Input engine
  Location& GetMutableLocation() { return location_; }

  // Temporary function until we have the update function in this class.
  AnimatedSprite& GetMutableSprite() { return sprite_; }

 private:
  AnimatedSprite sprite_;

  Location location_;
};

#endif
