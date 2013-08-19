#include "ionGL.h"
#include "Utilities.h"


namespace ion
{
	namespace GL
	{
		////////////
		// Params //
		////////////

		ImageTexture::Params::Params()
			: MinFilter(EFilter::Linear), MagFilter(EFilter::Linear), 
			MipMapMode(EMipMaps::Linear), WrapMode(EWrapMode::Repeat),
			MipMapLevels(8)
		{}
		
		ImageTexture::Params const & Texture::GetParams() const
		{
			return Parameters;
		}

		void ImageTexture::SetParams(Params const & params)
		{
			Parameters = params;
		}

		void ImageTexture::ApplyParams()
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

			glTexParameteri(GetTarget(), GL_TEXTURE_MIN_FILTER, FilterMatrix[(int) Parameters.MipMapMode][(int) Parameters.MinFilter]);
			glTexParameteri(GetTarget(), GL_TEXTURE_MAG_FILTER, FilterLookup[(int) Parameters.MagFilter]);

			if (Parameters.MipMapMode != EMipMaps::Disabled)
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

		ImageTexture::ImageTexture()
			: ImageLoaded(false)
		{}

		void ImageTexture::Bind()
		{
			CheckedGLCall(glBindTexture(GetTarget(), Handle));
		}

		void ImageTexture::Unbind()
		{
			CheckedGLCall(glBindTexture(GetTarget(), 0));
		}


		////////////
		// Lookup //
		////////////
		
		u32 const ImageTexture::InternalFormatMatrix[4][10] = 
		{
			{GL_R8, GL_R16, GL_R8UI, GL_R32UI, GL_R32UI, GL_R8I, GL_R16I, GL_R32I, GL_R16F, GL_R32F},
			{GL_RG8, GL_RG16, GL_RG8UI, GL_RG32UI, GL_RG32UI, GL_RG8I, GL_RG16I, GL_RG32I, GL_RG16F, GL_RG32F},
			{GL_RGB8, GL_RGB16, GL_RGB8UI, GL_RGB32UI, GL_RGB32UI, GL_RGB8I, GL_RGB16I, GL_RGB32I, GL_RGB16F, GL_RGB32F},
			{GL_RGBA8, GL_RGBA16, GL_RGBA8UI, GL_RGBA32UI, GL_RGBA32UI, GL_RGBA8I, GL_RGBA16I, GL_RGBA32I, GL_RGBA16F, GL_RGBA32F}
		};

		u32 const ImageTexture::FormatMatrix[4] = 
		{
			GL_R,
			GL_RG,
			GL_RGB,
			GL_RGBA
		};

		u32 const ImageTexture::TypeMatrix[7] = 
		{
			GL_UNSIGNED_BYTE,
			GL_UNSIGNED_SHORT,
			GL_UNSIGNED_INT,
			GL_BYTE,
			GL_SHORT,
			GL_INT,
			GL_FLOAT
		};


		//////////////
		// Variants //
		//////////////
		
		void Texture1D::Storage(u32 const width, EFormatComponents const components, EInternalFormatType const type)
		{
			Bind();
			glTexStorage1D(GL_TEXTURE_1D, Parameters.MipMapLevels, InternalFormatMatrix[(int) components][(int) type], Width = width);
			Unbind();
		}

		void Texture1D::Image(void * data, EFormatComponents const components, EFormatType const type)
		{
			Bind();
			glTexSubImage1D(GL_TEXTURE_1D, 0, 0, Width, FormatMatrix[(int) components], TypeMatrix[(int) type], data);
			ImageLoaded = true;
			ApplyParams();
			Unbind();
		}

		Texture1D::Texture1D()
			: Width()
		{}

		u32 Texture1D::GetTarget()
		{
			return GL_TEXTURE_1D;
		}
		
		void Texture2D::Storage(u32 const width, u32 const height, EFormatComponents const components, EInternalFormatType const type)
		{
			Bind();
			glTexStorage2D(GL_TEXTURE_2D, Parameters.MipMapLevels, InternalFormatMatrix[(int) components][(int) type], Width = width, Height = height);
			Unbind();
		}

		void Texture2D::Image(void * data, EFormatComponents const components, EFormatType const type)
		{
			Bind();
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, Width, Height, FormatMatrix[(int) components], TypeMatrix[(int) type], data);
			ImageLoaded = true;
			ApplyParams();
			Unbind();
		}

		Texture2D::Texture2D()
			: Width(), Height()
		{}

		u32 Texture2D::GetTarget()
		{
			return GL_TEXTURE_2D;
		}
		
		void Texture3D::Storage(u32 const width, u32 const height, u32 const depth, EFormatComponents const components, EInternalFormatType const type)
		{
			Bind();
			glTexStorage3D(GL_TEXTURE_3D, Parameters.MipMapLevels, InternalFormatMatrix[(int) components][(int) type], Width = width, Height = height, Depth = depth);
			Unbind();
		}

		void Texture3D::Image(void * data, EFormatComponents const components, EFormatType const type)
		{
			Bind();
			glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, Width, Height, Depth, FormatMatrix[(int) components], TypeMatrix[(int) type], data);
			ImageLoaded = true;
			ApplyParams();
			Unbind();
		}

		Texture3D::Texture3D()
			: Width(), Height()
		{}

		u32 Texture3D::GetTarget()
		{
			return GL_TEXTURE_3D;
		}
	}
}
