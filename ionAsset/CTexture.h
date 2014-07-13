
#pragma once

#include <ionGL.h>
#include "CImage.h"


class CTexture
{

public:

	CTexture();
	CTexture(CImage * Image);

	void SetImage(CImage * Image);
	void SetParams(ion::GL::Texture2D::Params const & Params);
	ion::GL::Texture2D::Params & SetParams();

	CImage * GetImage();
	ion::GL::Texture2D * GetHandle();

private:

	ion::GL::Texture2D * Handle = new ion::GL::Texture2D();
	CImage * Image = nullptr;

	ion::GL::Texture2D::Params Params;

};
