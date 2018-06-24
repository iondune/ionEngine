
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>

#include "Utilities.h"

#include <D3D11.h>


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			class CTexture : public virtual ITexture
			{

			public:
				
				static DXGI_FORMAT const InternalFormatMatrix[4][12];

				CTexture(ID3D11Device * Device, ID3D11DeviceContext * ImmediateContext);

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

				ID3D11Device * Device = nullptr;
				ID3D11DeviceContext * ImmediateContext = nullptr;
				ID3D11SamplerState * SamplerState = nullptr;
				ID3D11ShaderResourceView * ShaderResourceView = nullptr;

				EFilter MinFilter = EFilter::Linear;
				EFilter MagFilter = EFilter::Linear;
				EFilter MipMapFilter = EFilter::Linear;
				EWrapMode WrapMode = EWrapMode::Repeat;
				color4f BorderColor;

				//! Anisotrophic filtering value
				int Anisotropy = 0;

				bool MipMaps = true;
				bool IsInteger = false;

			};

			class CTexture2D : public ITexture2D, public CTexture
			{

			public:

				CTexture2D(
					ID3D11Device * Device, ID3D11DeviceContext * ImmediateContext,
					vec2i const & Size, ITexture::EMipMaps const MipMaps,
					ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type);

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

				ID3D11Texture2D * Texture2D = nullptr;

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
