
#pragma once

#include <ionCore.h>
#include <ionMath/SVector2.h>
#include <ionMath/SColor.h>


class CImage
{

public:

	static CImage * Load(std::string const & FileName);

	//! Deprecated, for backwards compatibility
	CImage(byte * const Data, uint const Width, uint const Height, bool const Alpha = false);
	CImage(byte * const Data, vec2u const Size, u8 const Channels);
	CImage(color4f const & Color, bool const Alpha = false);

	uint GetWidth() const;
	uint GetHeight() const;
	vec2u GetSize() const;
	uint GetStride() const;
	uint GetChannels() const;
	
	color4i GetPixel(uint const x, uint const y) const;
	void SetPixel(uint const x, uint const y, color4i const color);

	u8 const * GetImageData() const;
	u8 * GetImageData();

	bool HasAlpha() const;

	void Write(std::string const & fileName);
	void FlipY();

protected:

	uniquePtr<byte[]> Data;
	vec2u Size;
	u8 Channels;

};
