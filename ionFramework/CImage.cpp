
#include "CImage.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>


namespace ion
{

	CImage * CImage::Load(std::string const & FileName)
	{
		int x, y, n;
		byte * data = stbi_load(FileName.c_str(), & x, & y, & n, 0);

		if (! data)
		{
			std::cerr << "Failed to load image from file '" << FileName << "', reason: " << stbi_failure_reason() << std::endl;
			return 0;
		}

		CImage * Image = new CImage(data, vec2u(x, y), n);
		Image->FlipY();

		return Image;
	}

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

		uint Stride = GetStride();
		Data = uniquePtr<byte[]>(new u8[Size.X * Size.Y * Stride]);

		for (uint i = 0; i < Size.X * Size.Y; ++ i)
			for (uint j = 0; j < Stride; ++ j)
				Data[i*Stride + j] = (u8) (255.f * Color[j]);
	}

	uint CImage::GetWidth() const
	{
		return Size.X;
	}

	uint CImage::GetHeight() const
	{
		return Size.Y;
	}

	vec2u CImage::GetSize() const
	{
		return Size;
	}

	uint CImage::GetStride() const
	{
		return Channels;
	}

	uint CImage::GetChannels() const
	{
		return Channels;
	}

	color4i CImage::GetPixel(uint const x, uint const y) const
	{
		uint Stride = GetStride();

		return color4i(
			Data[x * Stride + y * Size.X * Stride + 0],
			Data[x * Stride + y * Size.X * Stride + 1],
			Data[x * Stride + y * Size.X * Stride + 2],
			Data[x * Stride + y * Size.X * Stride + 3]);
	}

	void CImage::SetPixel(uint const x, uint const y, color4i const color)
	{
		uint Stride = GetStride();

		for (uint i = 0; i < Stride; ++ i)
			Data[x * Stride + y * Size.X * Stride + i] = color[i];
	}

	u8 const * CImage::GetData() const
	{
		return Data.get();
	}

	u8 * CImage::GetData()
	{
		return Data.get();
	}

	bool CImage::HasAlpha() const
	{
		return Channels == 4;
	}

	void CImage::Write(std::string const & FileName)
	{
		uint Stride = GetStride();
		stbi_write_png(FileName.c_str(), Size.X, Size.Y, Stride, Data.get(), Size.X * Stride);
	}

	void CImage::FlipY()
	{
		uint Stride = GetStride();

		for (uint x = 0; x < Size.X; ++ x)
		{
			for (uint y = 0; y < Size.Y / 2; ++ y)
			{
				for (uint j = 0; j < Stride; ++ j)
					std::swap(Data[x * Stride + y * Size.X * Stride + j], Data[x * Stride + (Size.Y - 1 - y) * Size.X * Stride + j]);
			}
		}
	}

}
