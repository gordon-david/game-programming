#pragma once

#include <string>

namespace Image
{


	struct ImageData
	{
		int width;
		int height;
		int channels;
		unsigned char *data;

		~ImageData();
        friend std::ostream& operator<<(std::ostream& stream, const ImageData& imageData);
	};

	ImageData Load(const std::string filepath); 

}
