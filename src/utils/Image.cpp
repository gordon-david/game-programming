
#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION

#include "../vender/stb_image/stb_image.h"
#include <iostream>

namespace Image
{
    void init_stb()
    {
        static bool executed = false;
        if (executed)
            return;
        executed = true;
        
        stbi_set_flip_vertically_on_load(true);
        std::cout << "ran once" << std::endl;
    }

    ImageData::~ImageData()
    {
        stbi_image_free(data);
    }

    std::ostream &operator<<(std::ostream &stream, const ImageData &imageData)
    {
        stream << "ImageData: ("
               << "channels=" << imageData.channels
               << "width=" << imageData.width
               << "height=" << imageData.height
               << ")";
        return stream;
    }

    ImageData Load(const std::string filepath)
    {
        init_stb();
        int width, height, channels = -1;
        unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

        if (data == nullptr)
        {
            ImageData temp{width, height, channels, nullptr};
            std::cout << "ERROR: Failed to load image"
                      << temp << std::endl;
            return ImageData{};
        }

        return ImageData{width, height, channels, data};
    }
}
