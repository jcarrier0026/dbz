#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "location.h"
#include "sprite.h"

// GameObject is the top-level abstract base class that defines the interface
// that all objects in the game must implement.
//
// All drawn objects in the game (player, enemies, projectiles, objects, items)
// will extend from this base class.
class GameObject {
 public:
  virtual ~GameObject() = default;

  // Update this GameObject.
  virtual void Update() {}

  // Return the current location of the object.
  virtual Location GetLocation() const = 0;

  // Return the sprite for the object.
  virtual const Sprite& GetSprite() const = 0;
};

#endif
