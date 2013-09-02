
#pragma once

#include <string>
#include "SVector2.h"
#include <SColor.h>


class CImage
{

	friend class CImageLoader;

	unsigned char * ImageData;
	vec2u Size;

	bool Alpha;

public:

	static CImage * Load(std::string const & FileName);

	CImage(u8 * const imageData, u32 const width, u32 const height, bool const alpha = false);
	CImage(color4f const & Color, bool const Alpha = false);
	~CImage();

	u32 GetWidth() const;
	u32 GetHeight() const;
	vec2u GetSize() const;

	color4i GetPixel(u32 const x, u32 const y) const;

	u8 const * const GetImageData() const;
	u8 * GetImageData();

	bool const HasAlpha() const;

	void Write(std::string const & fileName);
	void FlipY();

};
