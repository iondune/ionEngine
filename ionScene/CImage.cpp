#include "CImage.h"

CImage::CImage(unsigned char * const imageData, int const width, int const height, bool const alpha)
    : ImageData(imageData), Width(width), Height(height), Alpha(alpha)
{}

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
