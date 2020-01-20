#include <iostream>
#include "graphics.h"

int main(int argc, char** argv) {
  Graphics graphics;
  // Returning 0 in main() means that the program executed successfully.
  if (!graphics.InitSuccess()) {
    return 1;
  }

  std::cout << "Press any key to exit" << std::endl;
  // Wait for user input before exiting.
  // If we didn't do this, the program would immediately terminate.
  // If we want to see the window, we need to make the program wait.
  std::cin.get();

  return 0;
}
