#include "textureLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../includes/stb.h"

TextureLoader::~TextureLoader() { dispose(); }

bool TextureLoader::loadTexture(std::string textureName) {
  std::string path =
      FilesystemHelper::getResourcePath(ResourceType::texture, textureName);

  stbi_set_flip_vertically_on_load(true);

  data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

  return data != nullptr;
}

unsigned char *TextureLoader::getData(int &imageWidth, int &imageHeight) {
  if(data != nullptr) {
    imageWidth = width;
    imageHeight = height;
    return data;
  }
  return nullptr;
}

void TextureLoader::dispose() {
  if (data != nullptr) {
    stbi_image_free(data);
    data = nullptr;
  }
}
