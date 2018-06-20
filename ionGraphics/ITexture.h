
#pragma once

#include <ionCore.h>
#include <ionMath.h>


namespace ion
{
	namespace Graphics
	{

		//! \ingroup ionGraphics
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
				Border = 3
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
				Fix16 = 1,
				Float16 = 2,
				Float32 = 3,
				SignedInt8 = 4,
				SignedInt16 = 5,
				SignedInt32 = 6,
				UnsignedInt8 = 7,
				UnsignedInt16 = 8,
				UnsignedInt32 = 9,
				DepthStencil = 10,
				//Depth32 = 11, // presently unsupported
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

			//! Sets the border color for this texture
			//! Used when WrapMode is set to EWrapMode::Border
			virtual void SetBorderColor(color4f const & BorderColor) = 0;

			//! Sets the anisotropy filtering value for this texture
			//! A value < 0 indicates that the max anisotrophy value should be used
			//! Default is -1
			virtual void SetAnisotropy(float const Anisotropy) = 0;

			virtual EFilter GetMinFilter() = 0;
			virtual EFilter GetMagFilter() = 0;
			virtual EFilter GetMipMapFilter() = 0;
			virtual EWrapMode GetWrapMode() = 0;
			virtual float GetAnisotropy() = 0;

			virtual void GenerateMipMaps() = 0;

		};

		//! \ingroup ionGraphics
		class ITexture2D : public virtual ITexture
		{

		public:

			virtual void Upload(void const * const Data, vec2i const & Size, EFormatComponents const Components, EScalarType const Type) = 0;
			virtual void UploadSubRegion(void const * const Data, vec2i const & Offset, vec2i const & Size, EFormatComponents const Components, EScalarType const Type) = 0;

			virtual void GetData(void * const Data, vec2i const & Size, EFormatComponents const Components, EScalarType const Type) = 0;

		};

		//! \ingroup ionGraphics
		class ITexture2DArray : public virtual ITexture
		{

		public:

			virtual void Upload(void const * const Data, vec3i const & Size, EFormatComponents const Components, EScalarType const Type) = 0;
			virtual void UploadSubRegion(void const * const Data, vec3i const & Offset, vec3i const & Size, EFormatComponents const Components, EScalarType const Type) = 0;

		};

		//! \ingroup ionGraphics
		class ITexture3D : public virtual ITexture
		{

		public:

			virtual void Upload(void const * const Data, vec3i const & Size, EFormatComponents const Components, EScalarType const Type) = 0;
			virtual void UploadSubRegion(void const * const Data, vec3i const & Offset, vec3i const & Size, EFormatComponents const Components, EScalarType const Type) = 0;

		};

		//! \ingroup ionGraphics
		class ITextureCubeMap : public virtual ITexture
		{

		public:

			enum class EFace
			{
				PositiveX = 0,
				NegativeX = 1,
				PositiveY = 2,
				NegativeY = 3,
				PositiveZ = 4,
				NegativeZ = 5
			};

			virtual void Upload(EFace const Face, void const * const Data, vec2i const & Size, EFormatComponents const Components, EScalarType const Type) = 0;
			virtual void UploadSubRegion(EFace const Face, void const * const Data, vec2i const & Offset, vec2i const & Size, EFormatComponents const Components, EScalarType const Type) = 0;

		};

	}
}
