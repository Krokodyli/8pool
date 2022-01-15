#include "drawable.h"

void Drawable::initDrawable() {
  textureID = -1;
  modelID = -1;
  hasTexture = false;
}

int Drawable::getTextureID() {
  return textureID;
}

int Drawable::getModelID() {
  return modelID;
}
