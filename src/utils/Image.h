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
	};

	ImageData Load(const std::string filepath); 

}
