#include "CImage.h"

#include <stb_image.c>


CImage * CImage::Load(std::string const & FileName)
{
	int x, y, n;
	u8 * data = stbi_load(FileName.c_str(), & x, & y, & n, 0);

	if (! data)
		return 0;

	CImage * Image = new CImage(data, x, y);
	Image->FlipY();

	return Image;
}

CImage::CImage(u8 * const imageData, u32 const width, u32 const height, bool const alpha)
    : ImageData(imageData), Size(width, height), Alpha(alpha)
{}

CImage::CImage(color4f const & Color, bool const alpha)
	: Size(2), Alpha(alpha)
{
	u32 Stride = Alpha ? 4 : 3;
	ImageData = new u8[4 * Stride];

	for (u32 i = 0; i < 4; ++ i)
		for (u32 j = 0; j < Stride; ++ j)
			ImageData[i*3 + j] = (u8) (255.f * Color[j]);
}

CImage::~CImage()
{
    delete ImageData;
}

u32 CImage::GetWidth() const
{
    return Size.X;
}

u32 CImage::GetHeight() const
{
    return Size.Y;
}

vec2u CImage::GetSize() const
{
	return Size;
}

color4i CImage::GetPixel(u32 const x, u32 const y) const
{
	u32 Stride = Alpha ? 4 : 3;

	return color4i(
		ImageData[x * Stride + y * Size.X * Stride + 0],
		ImageData[x * Stride + y * Size.X * Stride + 1],
		ImageData[x * Stride + y * Size.X * Stride + 2],
		ImageData[x * Stride + y * Size.X * Stride + 3]);
}

void CImage::SetPixel(u32 const x, u32 const y, color4i const color)
{
	u32 Stride = Alpha ? 4 : 3;

	for (u32 i = 0; i < Stride; ++ i)
		ImageData[x * Stride + y * Size.X * Stride + i] = color[i];
}

u8 const * const CImage::GetImageData() const
{
    return ImageData;
}

u8 * CImage::GetImageData()
{
    return ImageData;
}

bool const CImage::HasAlpha() const
{
	return Alpha;
}

#include "BitmapWriter.h"

void CImage::Write(std::string const & fileName)
{
	u32 Stride = Alpha ? 4 : 3;
	bitmap_image image(Size.X, Size.Y);

	for (u32 x = 0; x < Size.X; ++x)
	{
		for (u32 y = 0; y < Size.Y; ++y)
		{
			image.set_pixel(x, Size.Y - 1 - y, 
				ImageData[x * Stride + y * Size.X * Stride + 0], 
				ImageData[x * Stride + y * Size.X * Stride + 1],
				ImageData[x * Stride + y * Size.X * Stride + 2]);
		}
	}

    image.save_image(fileName.c_str());
}

void CImage::FlipY()
{
	u32 Stride = Alpha ? 4 : 3;

	for (u32 x = 0; x < Size.X; ++ x)
	{
		for (u32 y = 0; y < Size.Y / 2; ++ y)
		{
			for (u32 j = 0; j < Stride; ++ j)
				std::swap(ImageData[x * Stride + y * Size.X * Stride + j], ImageData[x * Stride + (Size.Y - 1 - y) * Size.X * Stride + j]);
		}
	}
}
