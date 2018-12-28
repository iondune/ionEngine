
#include "CImage.h"
#include "ionLogger.h"

#include <stb_image.h>
#include <stb_image_write.h>


namespace ion
{

	CImage * CImage::Load(std::string const & FileName)
	{
		int x, y, n;
		byte * data = stbi_load(FileName.c_str(), & x, & y, & n, 4);

		if (! data)
		{
			Log::Error("Failed to load image from file '%s', reason: %s", FileName, stbi_failure_reason());
			return 0;
		}

		CImage * Image = new CImage(data, vec2i(x, y));
		Image->FlipY();

		return Image;
	}

	CImage::CImage(byte * const Data, vec2i const Size)
	{
		this->Data = Data;
		this->Size = Size;
	}

	CImage::CImage(color4f const & Color)
	{
		this->Size = vec2i(2);

		int const Stride = 4;
		Data = new ion::byte[Size.X * Size.Y * Stride];

		for (int i = 0; i < Size.X * Size.Y; ++ i)
			for (int j = 0; j < Stride; ++ j)
				Data[i*Stride + j] = (ion::byte) (255.f * Color[j]);
	}

	CImage::~CImage()
	{
		delete[] Data;
	}

	int CImage::GetWidth() const
	{
		return Size.X;
	}

	int CImage::GetHeight() const
	{
		return Size.Y;
	}

	vec2i CImage::GetSize() const
	{
		return Size;
	}

	color4i CImage::GetPixel(int const i, int const j) const
	{
		int const Stride = 4;

		int const x = Clamp(i, 0, Size.X - 1);
		int const y = Clamp(j, 0, Size.Y - 1);

		return color4i(
			Data[x * Stride + y * Size.X * Stride + 0],
			Data[x * Stride + y * Size.X * Stride + 1],
			Data[x * Stride + y * Size.X * Stride + 2],
			Data[x * Stride + y * Size.X * Stride + 3]);
	}

	void CImage::SetPixel(int const x, int const y, color4i const color)
	{
		int const Stride = 4;

		for (int i = 0; i < Stride; ++ i)
			Data[x * Stride + y * Size.X * Stride + i] = color[i];
	}

	ion::byte const * CImage::GetData() const
	{
		return Data;
	}

	ion::byte * CImage::GetData()
	{
		return Data;
	}

	void CImage::Write(std::string const & FileName)
	{
		int const Stride = 4;
		stbi_write_png(FileName.c_str(), Size.X, Size.Y, Stride, Data, Size.X * Stride);
	}

	void CImage::FlipY()
	{
		int const Stride = 4;

		for (int x = 0; x < Size.X; ++ x)
		{
			for (int y = 0; y < Size.Y / 2; ++ y)
			{
				for (int j = 0; j < Stride; ++ j)
				{
					std::swap(Data[x * Stride + y * Size.X * Stride + j], Data[x * Stride + (Size.Y - 1 - y) * Size.X * Stride + j]);
				}
			}
		}
	}

	void CImage::Crop(vec2i const & Position, vec2i const & NewSize)
	{
		int const Stride = 4;

		byte * NewData = new ion::byte[NewSize.X * NewSize.Y * Stride];

		for (int x = Position.X; x < Position.X + NewSize.X; ++ x)
		{
			for (int y = Position.Y; y < Position.Y + NewSize.Y; ++ y)
			{
				int const newX = x - Position.X;
				int const newY = y - Position.Y;

				for (uint j = 0; j < Stride; ++ j)
				{
					NewData[newX * Stride + newY * NewSize.X * Stride + j] = Data[x * Stride + y * Size.X * Stride + j];
				}
			}
		}

		Data = NewData;
		Size = NewSize;
	}

}
