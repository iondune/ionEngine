#include "CTexture.h"

#ifdef __unix__
#include <GL/glu.h>
#endif

#include <iostream>

STextureCreationFlags::STextureCreationFlags()
{
	MipMaps = true;
	Wrap = GL_REPEAT;
	Filter = GL_LINEAR;
	PixelType = GL_UNSIGNED_BYTE;
	PixelInternalFormat = PixelFormat = 0;
}

void STextureCreationFlags::apply() const
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Wrap);
	if (MipMaps)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
			Filter == GL_LINEAR ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Filter);
	}
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Filter);
}

CTexture::CTexture(CImage * Image, STextureCreationFlags const flags)
	: TextureHandle(0), Size(), Flags(flags)
{
	if (Image)
	{
		Size.Width = Image->getWidth();
		Size.Height = Image->getHeight();

		glGenTextures(1, & TextureHandle);
		glBindTexture(GL_TEXTURE_2D, TextureHandle);

		Flags.apply();

		glTexImage2D(GL_TEXTURE_2D, 0, Image->hasAlpha() ? GL_RGBA8 : GL_RGB8, Size.Width, Size.Height, 0, 
			Image->hasAlpha() ? GL_RGBA : GL_RGB, Flags.PixelType, Image->getImageData());
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
	{
		std::cerr << "Aborting texture creation, image not loaded!" << std::endl;
	}
}

CTexture::CTexture(SColor const & Color, STextureCreationFlags const Flags)
{
	CImage * Image = new CImage(Color, false);

	Size.Width = Image->getWidth();
	Size.Height = Image->getHeight();

	glGenTextures(1, & TextureHandle);
	glBindTexture(GL_TEXTURE_2D, TextureHandle);

	Flags.apply();

	glTexImage2D(GL_TEXTURE_2D, 0, Image->hasAlpha() ? GL_RGBA8 : GL_RGB8, Size.Width, Size.Height, 0, 
		Image->hasAlpha() ? GL_RGBA : GL_RGB, Flags.PixelType, Image->getImageData());
	glBindTexture(GL_TEXTURE_2D, 0);
}

void CTexture::setImage(void const * const Data, bool const hasAlpha)
{
	glBindTexture(GL_TEXTURE_2D, TextureHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, Flags.PixelInternalFormat, Size.Width, Size.Height, 0, 
		Flags.PixelFormat, Flags.PixelType, Data);
	glBindTexture(GL_TEXTURE_2D, 0);
}
void CTexture::setImage(CImage * Image)
{
	if (Size.Width != Image->getWidth() || Size.Height != Image->getHeight())
		return;

	glBindTexture(GL_TEXTURE_2D, TextureHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, Image->hasAlpha() ? GL_RGBA8 : GL_RGB8, Size.Width, Size.Height, 0, 
		Image->hasAlpha() ? GL_RGBA : GL_RGB, Flags.PixelType, Image->getImageData());
	glBindTexture(GL_TEXTURE_2D, 0);
}

CTexture::CTexture(int const width, int const height, bool const Alpha, STextureCreationFlags const flags)
	: TextureHandle(0), Size(width, height), Flags(flags)
{
	glGenTextures(1, & TextureHandle);
	glBindTexture(GL_TEXTURE_2D, TextureHandle);

	Flags.apply();
	glTexImage2D(GL_TEXTURE_2D, 0, Flags.PixelInternalFormat ? Flags.PixelInternalFormat : (Alpha ? GL_RGBA : GL_RGB), 
		Size.Width, Size.Height, 0, 
		Flags.PixelFormat ? Flags.PixelFormat : (Alpha ? GL_RGBA : GL_RGB), Flags.PixelType, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
}

CTexture::CTexture(SPosition2 const & size, bool const Alpha, STextureCreationFlags const flags)
	: TextureHandle(0), Size(size), Flags(flags)
{
	glGenTextures(1, & TextureHandle);
	glBindTexture(GL_TEXTURE_2D, TextureHandle);

	Flags.apply();
	glTexImage2D(GL_TEXTURE_2D, 0, Flags.PixelInternalFormat ? Flags.PixelInternalFormat : (Alpha ? GL_RGBA : GL_RGB),
		Size.Width, Size.Height, 0, 
		Flags.PixelFormat ? Flags.PixelFormat : (Alpha ? GL_RGBA : GL_RGB), Flags.PixelType, 0);
	
	glBindTexture(GL_TEXTURE_2D, 0);
}

CTexture::CTexture(GLuint const textureHandle)
	: TextureHandle(textureHandle)
{
	GLint Width, Height;

	glBindTexture(GL_TEXTURE_2D, TextureHandle);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, & Width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, & Height);

	Size.Width = Width;
	Size.Height = Height;
}

CTexture::~CTexture()
{
	glDeleteTextures(1, & TextureHandle);
}

GLuint const CTexture::getTextureHandle() const
{
    return TextureHandle;
}

SSize2 const & CTexture::getSize() const
{
	return Size;
}

int const CTexture::getWidth() const
{
    return Size.Width;
}

int const CTexture::getHeight() const
{
    return Size.Height;
}

bool const CTexture::isValid() const
{
	return TextureHandle != 0;
}
