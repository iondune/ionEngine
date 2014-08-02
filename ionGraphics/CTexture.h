
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionAsset/CImage.h>

#include "IRenderTarget.h"


class STextureCreationFlags
{

public:

	STextureCreationFlags();

	bool MipMaps;
	u32 Wrap;
	u32 Filter;
	u32 PixelFormat;

	void Apply() const;

};

class CTexture : public IRenderTarget
{

public:

    CTexture(CImage * Image, STextureCreationFlags const Flags = STextureCreationFlags());
	CTexture(vec2u const & Size, bool const Alpha, STextureCreationFlags const Flags = STextureCreationFlags());
	CTexture(u32 const Handle);

	~CTexture();

    u32 const GetHandle() const;
	vec2i const & GetSize() const;
	bool const IsValid() const;

	void SetImage(CImage * Image);
	void SetImage(void const * const Data, u8 const Channels);

	virtual ERenderTargetType const GetRenderTargetType();

protected:

    u32 Handle;
	vec2i Size;

	STextureCreationFlags Flags;

};
