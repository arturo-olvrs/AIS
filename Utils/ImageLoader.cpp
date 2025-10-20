#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "ImageLoader.h"

namespace ImageLoader {
  Image load(const std::string& filename, bool flipY) {
    stbi_set_flip_vertically_on_load(flipY);
    int width, height, nrComponents;
    stbi_uc* image_data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (image_data) {
      const uint32_t uw = uint32_t(width);
      const uint32_t uh = uint32_t(height);
      const uint8_t uc = uint8_t(nrComponents);
      Image image(uw, uh, uc);

      std::copy(image_data,
                image_data + (width * height * nrComponents),
                image.data.begin());
      stbi_image_free(image_data);

      return image;
    } else {
      std::stringstream s;
      s << "Can't loaf image file " << filename;
      throw Exception(s.str());
    }
  }
}
