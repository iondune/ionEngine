#include "CTexture.h"

#include <GL/glew.h>
#include <ionGL.h>


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
	CheckedGLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Wrap));
	CheckedGLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Wrap));
	if (MipMaps)
	{
		CheckedGLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
			Filter == GL_LINEAR ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR_MIPMAP_NEAREST));
		CheckedGLCall(glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE));
	}
	else
	{
		CheckedGLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Filter));
	}
	
	CheckedGLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Filter));
}

CTexture::CTexture(CImage * Image, STextureCreationFlags const flags)
	: TextureHandle(0), Size(), Flags(flags)
{
	if (Image)
	{
		Size.X = Image->GetWidth();
		Size.Y = Image->GetHeight();

		CheckedGLCall(glGenTextures(1, & TextureHandle));
		CheckedGLCall(glBindTexture(GL_TEXTURE_2D, TextureHandle));

		Flags.apply();

		CheckedGLCall(glTexImage2D(GL_TEXTURE_2D, 0, Image->HasAlpha() ? GL_RGBA8 : GL_RGB8, Size.X, Size.Y, 0, 
			Image->HasAlpha() ? GL_RGBA : GL_RGB, Flags.PixelType, Image->GetImageData()));
		if (Flags.MipMaps && glGenerateMipmap)
			CheckedGLCall(glGenerateMipmap(GL_TEXTURE_2D));
		CheckedGLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}
	else
	{
		std::cerr << "Aborting texture creation, image not loaded!" << std::endl;
	}
}

CTexture::CTexture(SColorAf const & Color, STextureCreationFlags const Flags)
{
	CImage * Image = new CImage(Color, false);

	Size = Image->GetSize();

	CheckedGLCall(glGenTextures(1, & TextureHandle));
	CheckedGLCall(glBindTexture(GL_TEXTURE_2D, TextureHandle));

	Flags.apply();

	CheckedGLCall(glTexImage2D(GL_TEXTURE_2D, 0, Image->HasAlpha() ? GL_RGBA8 : GL_RGB8, Size.X, Size.Y, 0, 
		Image->HasAlpha() ? GL_RGBA : GL_RGB, Flags.PixelType, Image->GetImageData()));
	CheckedGLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void CTexture::setImage(void const * const Data, bool const hasAlpha)
{
	CheckedGLCall(glBindTexture(GL_TEXTURE_2D, TextureHandle));
	CheckedGLCall(glTexImage2D(GL_TEXTURE_2D, 0, Flags.PixelInternalFormat, Size.X, Size.Y, 0, 
		Flags.PixelFormat, Flags.PixelType, Data));
	CheckedGLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
void CTexture::setImage(CImage * Image)
{
	if (Size.X != Image->GetWidth() || Size.Y != Image->GetHeight())
		return;

	CheckedGLCall(glBindTexture(GL_TEXTURE_2D, TextureHandle));
	CheckedGLCall(glTexImage2D(GL_TEXTURE_2D, 0, Image->HasAlpha() ? GL_RGBA8 : GL_RGB8, Size.X, Size.Y, 0, 
		Image->HasAlpha() ? GL_RGBA : GL_RGB, Flags.PixelType, Image->GetImageData()));
	CheckedGLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

CTexture::CTexture(int const width, int const height, bool const Alpha, STextureCreationFlags const flags)
	: TextureHandle(0), Size(width, height), Flags(flags)
{
	CheckedGLCall(glGenTextures(1, & TextureHandle));
	CheckedGLCall(glBindTexture(GL_TEXTURE_2D, TextureHandle));

	Flags.apply();
	CheckedGLCall(glTexImage2D(GL_TEXTURE_2D, 0, Flags.PixelInternalFormat ? Flags.PixelInternalFormat : (Alpha ? GL_RGBA : GL_RGB), 
		Size.X, Size.Y, 0, 
		Flags.PixelFormat ? Flags.PixelFormat : (Alpha ? GL_RGBA : GL_RGB), Flags.PixelType, 0));

	CheckedGLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

CTexture::CTexture(vec2i const & size, bool const Alpha, STextureCreationFlags const flags)
	: TextureHandle(0), Size(size), Flags(flags)
{
	CheckedGLCall(glGenTextures(1, & TextureHandle));
	CheckedGLCall(glBindTexture(GL_TEXTURE_2D, TextureHandle));

	Flags.apply();
	CheckedGLCall(glTexImage2D(GL_TEXTURE_2D, 0, Flags.PixelInternalFormat ? Flags.PixelInternalFormat : (Alpha ? GL_RGBA : GL_RGB),
		Size.X, Size.Y, 0, 
		Flags.PixelFormat ? Flags.PixelFormat : (Alpha ? GL_RGBA : GL_RGB), Flags.PixelType, 0));
	
	CheckedGLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

CTexture::CTexture(GLuint const textureHandle)
	: TextureHandle(textureHandle)
{
	GLint Width, Height;

	CheckedGLCall(glBindTexture(GL_TEXTURE_2D, TextureHandle));
	CheckedGLCall(glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, & Width));
	CheckedGLCall(glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, & Height));

	Size.X = Width;
	Size.Y = Height;
}

CTexture::~CTexture()
{
	CheckedGLCall(glDeleteTextures(1, & TextureHandle));
}

GLuint const CTexture::getTextureHandle() const
{
    return TextureHandle;
}

vec2i const & CTexture::getSize() const
{
	return Size;
}

int const CTexture::getWidth() const
{
    return Size.X;
}

int const CTexture::getHeight() const
{
    return Size.Y;
}

bool const CTexture::isValid() const
{
	return TextureHandle != 0;
}

ERenderTargetType const CTexture::getRenderTargetType()
{
	return ERenderTargetType::Texture;
}
