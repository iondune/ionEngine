
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
				
				static u32 const InternalFormatMatrix[4][3];
				static u32 const FormatMatrix[4];

				static string const InternalFormatStringMatrix[4][10];
				static string const FormatStringMatrix[4];


				void SetMinFilter(EFilter const MinFilter);
				void SetMagFilter(EFilter const MagFilter);
				void SetMipMapFilter(EFilter const MipMapFilter);
				void SetWrapMode(EWrapMode const WrapMode);
				void SetAnisotropy(f32 const Anisotropy);

				EFilter GetMinFilter();
				EFilter GetMagFilter();
				EFilter GetMipMapFilter();
				EWrapMode GetWrapMode();
				f32 GetAnisotropy();
				
				void ApplyParams();
				virtual uint GetGLBindTextureTarget() const = 0;
				virtual uint GetGLTextureBindingEnum() const = 0;

				uint Handle = 0;

				EFilter MinFilter = EFilter::Linear;
				EFilter MagFilter = EFilter::Linear;
				EFilter MipMapFilter = EFilter::Linear;
				EWrapMode WrapMode = EWrapMode::Repeat;

				//! Anisotrophic filtering value
				//! A value < 0 indicates that the max anisotrophy value should be used
				f32 Anisotropy = -1;

				bool MipMaps = true;

			};

			class CTexture2D : public ITexture2D, public CTexture
			{

			public:

				void Upload(void const * const Data, vec2u const & Size, EFormatComponents const Components, EScalarType const Type);
				void UploadSubRegion(void const * const Data, vec2u const & Offset, vec2u const & Size, EFormatComponents const Components, EScalarType const Type);

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

				vec2u TextureSize;

#pragma warning(suppress: 4250)
			};

			class CTexture3D : public ITexture3D, public CTexture
			{

			public:
				
				void Upload(void const * const Data, vec3u const & Size, EFormatComponents const Components, EScalarType const Type);
				void UploadSubRegion(void const * const Data, vec3u const & Offset, vec3u const & Size, EFormatComponents const Components, EScalarType const Type);

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

				vec3u TextureSize;

#pragma warning(suppress: 4250)
			};

		}
	}
}
