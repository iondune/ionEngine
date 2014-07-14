
#pragma once

#include <ionGL.h>
#include "CImage.h"


typedef ion::GL::Texture2D::Params STextureParams;

class CTexture
{

public:

	CTexture();
	CTexture(CImage * Image, STextureParams const & Params = STextureParams{});

	void SetImage(CImage * Image);
	void SetParams(STextureParams const & Params);
	STextureParams & SetParams();

	CImage * GetImage();
	ion::GL::Texture2D * GetHandle();

private:

	ion::GL::Texture2D * Handle = new ion::GL::Texture2D();
	CImage * Image = nullptr;

	STextureParams Params;

};
