
#include "CTexture.h"


CTexture::CTexture()
{}

CTexture::CTexture(CImage * Image, STextureParams const & Params)
{
	SetParams(Params);
	SetImage(Image);
}

void CTexture::SetImage(CImage * Image)
{
	this->Image = Image;

	if (Image)
	{
		Handle->SetParams(Params);
		Handle->Image(Image->GetData(), Image->GetSize(), ion::GL::ImageTexture::EFormatComponents::RGB);
	}
}

void CTexture::SetParams(ion::GL::Texture2D::Params const & Params)
{
	this->Params = Params;
	Handle->SetParams(Params);
}

ion::GL::Texture2D::Params & CTexture::SetParams()
{
	Handle->SetParams(Params);
	return Params;
}

CImage * CTexture::GetImage()
{
	return Image;
}

ion::GL::Texture2D * CTexture::GetHandle()
{
	return Handle;
}
