#include "CImage.h"

CImage::CImage(unsigned char * const imageData, int const width, int const height, bool const alpha)
    : ImageData(imageData), Width(width), Height(height), Alpha(alpha)
{}


CImage::CImage(SColor const & Color, bool const alpha)
	: Width(2), Height(2), Alpha(alpha)
{
	int Stride = Alpha ? 4 : 3;
	ImageData = new unsigned char[4 * Stride];
	for (int i = 0; i < 4; ++ i)
		for (int j = 0; j < Stride; ++ j)
			ImageData[i*3 + j] = (unsigned char) (255.f * Color[j]);
}

CImage::~CImage()
{
    delete ImageData;
}

int const CImage::getWidth() const
{
    return Width;
}

int const CImage::getHeight() const
{
    return Height;
}

unsigned char const * const CImage::getImageData() const
{
    return ImageData;
}

unsigned char * CImage::getImageData()
{
    return ImageData;
}

bool const CImage::hasAlpha() const
{
	return Alpha;
}

#include "ImageLoaders/BitmapWriter.hpp"

void CImage::write(std::string const & fileName)
{
	int Stride = Alpha ? 4 : 3;
	bitmap_image image(Width, Height);

	for (int x = 0; x < Width; ++x)
	{
		for (int y = 0; y < Height; ++y)
		{
			image.set_pixel(x, Height - 1 - y, 
				ImageData[x * Stride + y * Width * Stride + 0], 
				ImageData[x * Stride + y * Width * Stride + 1],
				ImageData[x * Stride + y * Width * Stride + 2]
				);
		}
	}

    image.save_image(fileName.c_str());
}
