
#pragma once

#include <ionMath.h>


namespace ion
{

	class CImage
	{

	public:

		static CImage * Load(std::string const & FileName);

		CImage(byte * const Data, vec2u const Size, u8 const Channels);
		CImage(color4f const & Color, bool const Alpha = false);

		uint GetWidth() const;
		uint GetHeight() const;
		vec2u GetSize() const;
		uint GetStride() const;
		uint GetChannels() const;

		color4i GetPixel(uint const x, uint const y) const;
		void SetPixel(uint const x, uint const y, color4i const color);

		u8 const * GetData() const;
		u8 * GetData();

		bool HasAlpha() const;

		void Write(std::string const & fileName);
		void FlipY();

	protected:

		uniquePtr<byte[]> Data;
		vec2u Size;
		u8 Channels;

	};

}
