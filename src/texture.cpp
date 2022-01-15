#include "texture.h"

Texture::~Texture() {
  if(isLoaded)
    glDeleteTextures(1, &id);
}

bool Texture::load(std::string textureName) {
  TextureLoader textureLoader;
  if(!textureLoader.loadTexture(textureName))
    return false;

  unsigned char *imageBytes;
  int width, height;
  imageBytes = textureLoader.getData(width, height);

  generateAndBindTexture();
  setTextureParameters();
  loadData(imageBytes, width, height);
  //createMipmaps();
  return true;
}

void Texture::bind() {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::generateAndBindTexture() {
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::setTextureParameters() {
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::loadData(unsigned char *data, int width, int height) {
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
               0, GL_RGB, GL_UNSIGNED_BYTE, data);
}

void Texture::createMipmaps() {
  glGenerateMipmap(GL_TEXTURE_2D);
}
