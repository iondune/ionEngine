
#pragma once

#include "vec2.h"
#include "color4.h"


namespace ion
{

	class CImage
	{

	public:

		static CImage * Load(std::string const & FileName);

		CImage(ion::byte * const Data, vec2i const Size, int const Channels);
		CImage(color4f const & Color, bool const Alpha = false);
		~CImage();

		int GetWidth() const;
		int GetHeight() const;
		vec2i GetSize() const;
		int GetStride() const;
		int GetChannels() const;

		color4i GetPixel(int const x, int const y) const;
		void SetPixel(int const x, int const y, color4i const color);

		ion::byte const * GetData() const;
		ion::byte * GetData();

		bool HasAlpha() const;

		void Write(std::string const & fileName);
		void FlipY();

		void Crop(vec2i const & Position, vec2i const & Size);

	protected:

		byte * Data;
		vec2i Size;
		int Channels;

	};

}
