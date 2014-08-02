#include "CTexture.h"

#include <GL/glew.h>


STextureCreationFlags::STextureCreationFlags()
{
	MipMaps = true;
	Wrap = GL_REPEAT;
	Filter = GL_LINEAR;
	PixelFormat = GL_RGBA;
}

void STextureCreationFlags::Apply() const
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Wrap);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Filter);
	if (MipMaps)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			Filter == GL_LINEAR ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR_MIPMAP_NEAREST);
	else
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Filter);
}

CTexture::CTexture(CImage * Image, STextureCreationFlags const Flags)
: Handle(0)
{
	this->Flags = Flags;

	if (Image)
	{
		Size.X = Image->GetWidth();
		Size.Y = Image->GetHeight();

		glGenTextures(1, & Handle);
		SetImage(Image);
	}
	else
	{
		std::cerr << "Aborting texture creation, image not loaded!" << std::endl;
	}
}

CTexture::CTexture(vec2u const & Size, bool const Alpha, STextureCreationFlags const Flags)
: Handle(0)
{
	this->Size = Size;
	this->Flags = Flags;

	glGenTextures(1, & Handle);
	SetImage(0, Alpha ? 4 : 3);
}

CTexture::CTexture(GLuint const textureHandle)
: Handle(textureHandle)
{
	GLint Width, Height;

	glBindTexture(GL_TEXTURE_2D, Handle);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, & Width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, & Height);

	Size.X = Width;
	Size.Y = Height;
}

void CTexture::SetImage(void const * const Data, u8 const Channels)
{
	uint Format = 0;
	switch (Channels)
	{
	default:
	case 1:
		Format = GL_RED;
		break;
	case 2:
		Format = GL_RG;
		break;
	case 3:
		Format = GL_RGB;
		break;
	case 4:
		Format = GL_RGBA;
		break;
	}

	glBindTexture(GL_TEXTURE_2D, Handle);
	Flags.Apply();
	glTexImage2D(GL_TEXTURE_2D, 0, Flags.PixelFormat, Size.X, Size.Y, 0,
		Format, GL_UNSIGNED_BYTE, Data);
	if (Flags.MipMaps)
		glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void CTexture::SetImage(CImage * Image)
{
	SetImage(Image->GetData(), Image->GetChannels());
}

CTexture::~CTexture()
{
	glDeleteTextures(1, & Handle);
}

GLuint const CTexture::GetHandle() const
{
    return Handle;
}

vec2i const & CTexture::GetSize() const
{
	return Size;
}

bool const CTexture::IsValid() const
{
	return Handle != 0;
}

ERenderTargetType const CTexture::GetRenderTargetType()
{
	return ERenderTargetType::Texture;
}
