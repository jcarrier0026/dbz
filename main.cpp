#include <iostream>
#include "game.h"

int main(int argc, char** argv) {
  Game game;

  if (!game.Run()) {
    // Nonzero return value from main indicates something went wrong.
    return 1;
  }

  return 0;
}
