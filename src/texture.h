#pragma once

#include "filesystemHelper.h"
#include "glad.h"
#include "glfw.h"
#include "textureLoader.h"
#include <string>

class Texture {
private:
  bool isLoaded = false;
  unsigned int id = 0;

  void generateAndBindTexture();
  void setTextureParameters();
  void loadData(unsigned char *data, int width, int height);
  void createMipmaps();

public:
  Texture();
  Texture(const Texture &r) = delete;
  ~Texture();

  bool load(std::string textureName);
  void bind();
};
