
#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION

#include "../vender/stb_image/stb_image.h"

namespace Image
{
	ImageData::~ImageData()
	{
		stbi_image_free(data);
	}

	ImageData Load(const std::string filepath)
	{
		int width, height, channels;
		unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
		
		if(data == nullptr)
		{
			// TODO error handling and logging
		}

		return ImageData{width, height, channels, data}; 
	}
}
