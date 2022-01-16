#pragma once

#include <string>
#include "../../filesystemHelper.h"

class TextureLoader {
private:
  unsigned char *data = nullptr;
  int width, height, nrChannels;
public:
  ~TextureLoader();

  bool loadTexture(std::string textureName);
  unsigned char *getData(int &imageWidth, int &imageHeight);

  void dispose();
};
