#include "ionGL.h"
#include "Utilities.h"


namespace ion
{
	namespace GL
	{
		////////////
		// Params //
		////////////

		Texture::Params::Params()
			: MinFilter(EFilter::Linear), MagFilter(EFilter::Linear), 
			MipMapMode(EMipMaps::Linear), WrapMode(EWrapMode::Repeat)
		{}

		Texture::Params const & Texture::GetParams() const
		{
			return Parameters;
		}

		void Texture::SetParams(Params const & params)
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

		void Texture::Delete()
		{
			delete this;
		}

		Texture::~Texture()
		{
			glDeleteTextures(1, & Handle);
		}

		Texture::Texture()
		{
			glGenTextures(1, & Handle);
		}

		void Texture::Bind()
		{
			CheckedGLCall(glBindTexture(GetTarget(), Handle));
		}

		void Texture::Unbind()
		{
			CheckedGLCall(glBindTexture(GetTarget(), 0));
		}


		//////////////
		// Variants //
		//////////////

		u32 Texture1D::GetTarget()
		{
			return GL_TEXTURE_1D;
		}

		u32 Texture2D::GetTarget()
		{
			return GL_TEXTURE_2D;
		}

		u32 Texture3D::GetTarget()
		{
			return GL_TEXTURE_3D;
		}
	}
}
