#include "ionGL.h"
#include "Utilities.h"


////////////
// Params //
////////////

GL::Texture::Params::Params()
	: MinFilter(EFilter::Linear), MagFilter(EFilter::Linear), 
	MipMapMode(EMipMaps::Linear), WrapMode(EWrapMode::Repeat)
{}

GL::Texture::Params const & GL::Texture::GetParams() const
{
	return Parameters;
}

void GL::Texture::SetParams(Params const & params)
{
	static u32 const FilterMatrix[3][2] = 
	{
		{GL_NEAREST, GL_LINEAR},
		{GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST},
		{GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR},
	};

	static u32 const FilterLookup[2] = 
	{
		GL_NEAREST, GL_LINEAR
	};

	static u32 const WrapLookup[3] = 
	{
		GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT, GL_REPEAT
	};

	Parameters = params;
	
	glTexParameteri(GetTarget(), GL_TEXTURE_MIN_FILTER, FilterMatrix[(int) Parameters.MipMapMode][(int) Parameters.MinFilter]);
	glTexParameteri(GetTarget(), GL_TEXTURE_MAG_FILTER, FilterLookup[(int) Parameters.MagFilter]);

	if (Parameters.MipMapMode != Params::EMipMaps::Disabled)
		glTexParameteri(GetTarget(), GL_GENERATE_MIPMAP, GL_TRUE);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapLookup[(int) Parameters.WrapMode]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapLookup[(int) Parameters.WrapMode]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, WrapLookup[(int) Parameters.WrapMode]);
}


/////////////
// Texture //
/////////////

void GL::Texture::Delete()
{
	delete this;
}

GL::Texture::~Texture()
{
	glDeleteTextures(1, & Handle);
}

GL::Texture::Texture()
{
	glGenTextures(1, & Handle);
}

void GL::Texture::Bind()
{
	CheckedGLCall(glBindTexture(GetTarget(), Handle));
}

void GL::Texture::Unbind()
{
	CheckedGLCall(glBindTexture(GetTarget(), 0));
}


//////////////
// Variants //
//////////////

u32 GL::Texture1D::GetTarget()
{
	return GL_TEXTURE_1D;
}

u32 GL::Texture2D::GetTarget()
{
	return GL_TEXTURE_2D;
}

u32 GL::Texture3D::GetTarget()
{
	return GL_TEXTURE_3D;
}
