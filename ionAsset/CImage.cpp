#include "CImage.h"

#include <stb_image.c>
#include <stb_image_write.c>


CImage * CImage::Load(std::string const & FileName)
{
	int x, y, n;
	byte * data = stbi_load(FileName.c_str(), & x, & y, & n, 0);

	if (! data)
	{
		std::cerr << "Failed to load image from file '" << FileName << "', reason: " << stbi_failure_reason() << std::endl;
		return 0;
	}

	CImage * Image = new CImage(data, x, y);
	Image->FlipY();

	return Image;
}

CImage::CImage(byte * const Data, uint const Width, uint const Height, bool const Alpha)
: CImage(Data, vec2u(Width, Height), Alpha ? 4 : 3)
{}

CImage::CImage(byte * const Data, vec2u const Size, u8 const Channels)
{
	this->Data = uniquePtr<byte[]>(Data);
	this->Size = Size;
	this->Channels = Channels;
}

CImage::CImage(color4f const & Color, bool const Alpha)
{
	this->Size = vec2u(2);
	this->Channels = (Alpha ? 4 : 3);

	u32 Stride = GetStride();
	Data = uniquePtr<byte[]>(new u8[Size.X * Size.Y * Stride]);

	for (u32 i = 0; i < Size.X * Size.Y; ++ i)
		for (u32 j = 0; j < Stride; ++ j)
			Data[i*Stride + j] = (u8) (255.f * Color[j]);
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

u32 CImage::GetStride() const
{
	return Size.Y;
}

u32 CImage::GetChannels() const
{
	return Channels;
}

color4i CImage::GetPixel(u32 const x, u32 const y) const
{
	u32 Stride = GetStride();

	return color4i(
		Data[x * Stride + y * Size.X * Stride + 0],
		Data[x * Stride + y * Size.X * Stride + 1],
		Data[x * Stride + y * Size.X * Stride + 2],
		Data[x * Stride + y * Size.X * Stride + 3]);
}

void CImage::SetPixel(u32 const x, u32 const y, color4i const color)
{
	u32 Stride = GetStride();

	for (u32 i = 0; i < Stride; ++ i)
		Data[x * Stride + y * Size.X * Stride + i] = color[i];
}

u8 const * CImage::GetImageData() const
{
	return Data.get();
}

u8 * CImage::GetImageData()
{
	return Data.get();
}

bool CImage::HasAlpha() const
{
	return Channels == 4;
}

void CImage::Write(std::string const & FileName)
{
	u32 Stride = GetStride();
	stbi_write_png(FileName.c_str(), Size.X, Size.Y, Stride, Data.get(), Size.X * Stride);
}

void CImage::FlipY()
{
	u32 Stride = GetStride();

	for (u32 x = 0; x < Size.X; ++ x)
	{
		for (u32 y = 0; y < Size.Y / 2; ++ y)
		{
			for (u32 j = 0; j < Stride; ++ j)
				std::swap(Data[x * Stride + y * Size.X * Stride + j], Data[x * Stride + (Size.Y - 1 - y) * Size.X * Stride + j]);
		}
	}
}
