
#include "CTexture.h"


CTexture::CTexture()
{}

CTexture::CTexture(CImage * Image)
{
	SetImage(Image);
}

void CTexture::SetImage(CImage * Image)
{
	this->Image = Image;

	Handle->SetParams(Params);
	Handle->Image(Image->GetData(), Image->GetSize(), ion::GL::ImageTexture::EFormatComponents::RGB);
}

void CTexture::SetParams(ion::GL::Texture2D::Params const & Params)
{
	this->Params = Params;
}

ion::GL::Texture2D::Params & CTexture::SetParams()
{
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
