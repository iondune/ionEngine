
#pragma once

#include <ionCore.h>
#include <ionMath.h>

#include "CImage.h"
#include "IRenderTarget.h"


class STextureCreationFlags
{

public:

	STextureCreationFlags();

	bool MipMaps;
	u32 Wrap;
	u32 Filter;
	u32 PixelInternalFormat;
	u32 PixelFormat;
	u32 PixelType;

	void apply() const;

};

class CTexture : public IRenderTarget
{

public:

    CTexture(CImage * Image, STextureCreationFlags const Flags = STextureCreationFlags());
    CTexture(SColorAf const & Color, STextureCreationFlags const Flags = STextureCreationFlags());
	CTexture(int const Width, int const Height, bool const Alpha, STextureCreationFlags const Flags = STextureCreationFlags());
	CTexture(vec2i const & size, bool const Alpha, STextureCreationFlags const Flags = STextureCreationFlags());
	CTexture(u32 const textureHandle);

	~CTexture();

    u32 const getTextureHandle() const;

	vec2i const & getSize() const;
    int const getWidth() const;
    int const getHeight() const;

	bool const isValid() const;

	void setImage(CImage * Image);
	void setImage(void const * const Data, bool const hasAlpha);

	virtual ERenderTargetType const getRenderTargetType();

protected:

    u32 TextureHandle;
	vec2i Size;

	STextureCreationFlags Flags;

};
