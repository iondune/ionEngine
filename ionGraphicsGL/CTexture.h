
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>

#include "Utilities.h"


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{

			class CTexture : public virtual ITexture
			{

			public:
				
				static uint const InternalFormatMatrix[4][11];
				static uint const FormatMatrix[4][2];

				static string const InternalFormatStringMatrix[4][10];
				static string const FormatStringMatrix[4];


				void SetMinFilter(EFilter const MinFilter);
				void SetMagFilter(EFilter const MagFilter);
				void SetMipMapFilter(EFilter const MipMapFilter);
				void SetWrapMode(EWrapMode const WrapMode);
				void SetBorderColor(color4f const & BorderColor);
				void SetAnisotropy(float const Anisotropy);

				EFilter GetMinFilter();
				EFilter GetMagFilter();
				EFilter GetMipMapFilter();
				EWrapMode GetWrapMode();
				float GetAnisotropy();

				void GenerateMipMaps();

				void ApplyParams();
				virtual uint GetGLBindTextureTarget() const = 0;
				virtual uint GetGLTextureBindingEnum() const = 0;

				uint Handle = 0;

				EFilter MinFilter = EFilter::Linear;
				EFilter MagFilter = EFilter::Linear;
				EFilter MipMapFilter = EFilter::Linear;
				EWrapMode WrapMode = EWrapMode::Repeat;
				color4f BorderColor;

				//! Anisotrophic filtering value
				//! A value < 0 indicates that the max anisotrophy value should be used
				float Anisotropy = -1;

				bool MipMaps = true;
				bool IsInteger = false;

			};

			class CTexture2D : public ITexture2D, public CTexture
			{

			public:

				void Upload(void const * const Data, vec2i const & Size, EFormatComponents const Components, EScalarType const Type);
				void UploadSubRegion(void const * const Data, vec2i const & Offset, vec2i const & Size, EFormatComponents const Components, EScalarType const Type);

				void GetData(void * const Data, vec2i const & Size, EFormatComponents const Components, EScalarType const Type);

				using CTexture::SetMinFilter;
				using CTexture::SetMagFilter;
				using CTexture::SetMipMapFilter;
				using CTexture::SetWrapMode;
				using CTexture::SetAnisotropy;
				using CTexture::GetMinFilter;
				using CTexture::GetMagFilter;
				using CTexture::GetMipMapFilter;
				using CTexture::GetWrapMode;
				using CTexture::GetAnisotropy;

				uint GetGLBindTextureTarget() const;
				uint GetGLTextureBindingEnum() const;

				vec2i TextureSize;

#pragma warning(suppress: 4250)
			};

			class CTexture2DArray : public ITexture2DArray, public CTexture
			{

			public:

				void Upload(void const * const Data, vec3i const & Size, EFormatComponents const Components, EScalarType const Type);
				void UploadSubRegion(void const * const Data, vec3i const & Offset, vec3i const & Size, EFormatComponents const Components, EScalarType const Type);

				using CTexture::SetMinFilter;
				using CTexture::SetMagFilter;
				using CTexture::SetMipMapFilter;
				using CTexture::SetWrapMode;
				using CTexture::SetAnisotropy;
				using CTexture::GetMinFilter;
				using CTexture::GetMagFilter;
				using CTexture::GetMipMapFilter;
				using CTexture::GetWrapMode;
				using CTexture::GetAnisotropy;

				uint GetGLBindTextureTarget() const;
				uint GetGLTextureBindingEnum() const;

				vec3i TextureSize;

#pragma warning(suppress: 4250)
			};

			class CTexture3D : public ITexture3D, public CTexture
			{

			public:

				void Upload(void const * const Data, vec3i const & Size, EFormatComponents const Components, EScalarType const Type);
				void UploadSubRegion(void const * const Data, vec3i const & Offset, vec3i const & Size, EFormatComponents const Components, EScalarType const Type);

				using CTexture::SetMinFilter;
				using CTexture::SetMagFilter;
				using CTexture::SetMipMapFilter;
				using CTexture::SetWrapMode;
				using CTexture::SetAnisotropy;
				using CTexture::GetMinFilter;
				using CTexture::GetMagFilter;
				using CTexture::GetMipMapFilter;
				using CTexture::GetWrapMode;
				using CTexture::GetAnisotropy;

				uint GetGLBindTextureTarget() const;
				uint GetGLTextureBindingEnum() const;

				vec3i TextureSize;

#pragma warning(suppress: 4250)
			};

			class CTextureCubeMap : public ITextureCubeMap, public CTexture
			{

			public:

				void Upload(EFace const Face, void const * const Data, vec2i const & Size, EFormatComponents const Components, EScalarType const Type);
				void UploadSubRegion(EFace const Face, void const * const Data, vec2i const & Offset, vec2i const & Size, EFormatComponents const Components, EScalarType const Type);

				using CTexture::SetMinFilter;
				using CTexture::SetMagFilter;
				using CTexture::SetMipMapFilter;
				using CTexture::SetWrapMode;
				using CTexture::SetAnisotropy;
				using CTexture::GetMinFilter;
				using CTexture::GetMagFilter;
				using CTexture::GetMipMapFilter;
				using CTexture::GetWrapMode;
				using CTexture::GetAnisotropy;

				uint GetGLBindTextureTarget() const;
				uint GetGLTextureBindingEnum() const;

				vec2i TextureSize;

#pragma warning(suppress: 4250)
			};

		}
	}
}
