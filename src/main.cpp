#include <iostream>
#include <exception>
#include <stdexcept>
#include "utils/filesystemHelper.h"
#include "window.h"

int main(int argc, char** argv) {
  FilesystemHelper::init(argv[0]);
  Window window(1600, 900, "8pool");
  try {
    window.init();
  } catch(std::exception &ex) {
    std::cout << "Window init error: " << ex.what() << std::endl;
    return -1;
  }
  window.runLoop();
  return 0;
}
