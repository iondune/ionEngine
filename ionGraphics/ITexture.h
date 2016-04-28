
#pragma once

#include <ionCore.h>
#include <ionMath.h>


namespace ion
{
	namespace Graphics
	{

		class ITexture
		{
		public:

			////////////////////
			// Texture Params //
			////////////////////

			enum class EFilter
			{
				Nearest = 0,
				Linear = 1,
			};

			enum class EWrapMode
			{
				Clamp = 0,
				Mirror = 1,
				Repeat = 2,
			};

			enum class EFormatComponents
			{
				R = 0,
				RG = 1,
				RGB = 2,
				RGBA = 3,
			};

			enum class EInternalFormatType
			{
				Fix8 = 0,
				Float16 = 1,
				Float32 = 2,
				Depth = 3,
			};

			enum class EMipMaps
			{
				False = 0,
				True = 1,
			};

			//! Sets the minimizing filter for this texture
			//! Default is EFilter::Linear
			virtual void SetMinFilter(EFilter const MinFilter) = 0;

			//! Sets the maximizing filter for this texture
			//! Default is EFilter::Linear
			virtual void SetMagFilter(EFilter const MagFilter) = 0;

			//! Sets the mip map filter for this texture
			//! Default is EFilter::Linear
			virtual void SetMipMapFilter(EFilter const MipMapFilter) = 0;

			//! Sets the wrap mode for this texture
			//! Default is EWrapMode::Repeat
			virtual void SetWrapMode(EWrapMode const WrapMode) = 0;

			//! Sets the anisotropy filtering value for this texture
			//! A value < 0 indicates that the max anisotrophy value should be used
			//! Default is -1
			virtual void SetAnisotropy(float const Anisotropy) = 0;

			virtual EFilter GetMinFilter() = 0;
			virtual EFilter GetMagFilter() = 0;
			virtual EFilter GetMipMapFilter() = 0;
			virtual EWrapMode GetWrapMode() = 0;
			virtual float GetAnisotropy() = 0;

		};

		class ITexture2D : public virtual ITexture
		{

		public:

			virtual void Upload(void const * const Data, vec2u const & Size, EFormatComponents const Components, EScalarType const Type) = 0;
			virtual void UploadSubRegion(void const * const Data, vec2u const & Offset, vec2u const & Size, EFormatComponents const Components, EScalarType const Type) = 0;

		};

		class ITexture3D : public virtual ITexture
		{

		public:

			virtual void Upload(void const * const Data, vec3u const & Size, EFormatComponents const Components, EScalarType const Type) = 0;
			virtual void UploadSubRegion(void const * const Data, vec3u const & Offset, vec3u const & Size, EFormatComponents const Components, EScalarType const Type) = 0;

		};

	}
}
