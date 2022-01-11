#include <iostream>
#include <exception>
#include <stdexcept>
#include "window.h"

int main() {
  Window window(800, 600, "My window");
  try {
  window.init();
  } catch(std::exception &ex) {
    std::cout << "Window init error: " << ex.what() << std::endl;
    return -1;
  }
  window.runLoop();
  return 0;
}
