
#pragma once

#include <ionCore.h>
#include <ionMath.h>

#include "Utilities.h"


namespace ion
{
	namespace GL
	{
		class Texture
		{
		public:
			
			void Delete();
			~Texture();

		protected:

			Texture();
			
			u32 Handle = 0;
		};

		class ImageTexture : public Texture
		{
		public:

			enum class EFilter
			{
				Nearest = 0,
				Linear = 1
			};

			enum class EMipMaps
			{
				Disabled = 0,
				Nearest = 1,
				Linear = 2
			};

			enum class EWrapMode
			{
				Clamp = 0,
				Mirror = 1,
				Repeat = 2
			};

			enum class EFormatComponents
			{
				R = 0,
				RG = 1,
				RGB = 2,
				RGBA = 3
			};

			enum class EInternalFormatType
			{
				Fix8 = 0,
				Fix16 = 1,
				U8 = 2,
				U16 = 3,
				U32 = 4,
				S8 = 5,
				S16 = 6,
				S32 = 7,
				F16 = 8,
				F32 = 9
			};
			
			static u32 const InternalFormatMatrix[4][10];
			static u32 const FormatMatrix[4];

			struct Params
			{

				EFilter MinFilter;
				EFilter MagFilter;
				EMipMaps MipMapMode;
				EWrapMode WrapMode;
				u32 MipMapLevels;

				Params();
			};
			
			Params const & GetParams() const;
			void SetParams(Params const & params);
			
			void Activate(uint const index);
			void Deactivate(uint const index);

		protected:

			ImageTexture();
			
			void ApplyParams();

			void Bind();
			void Unbind();
			virtual u32 GetTarget() = 0;

			u32 Handle;
			Params Parameters;
			bool ImageLoaded;
		};

		class Texture1D : public ImageTexture
		{

		public:

			void Storage(u32 const size, EFormatComponents const components = EFormatComponents::RGBA, EInternalFormatType const type = EInternalFormatType::U8);
			void Image(void * const data, EFormatComponents const components = EFormatComponents::RGBA, EFormatType const type = EFormatType::U8);
			void SubImage(void * const data, u32 const offset, u32 const size, EFormatComponents const components = EFormatComponents::RGBA, EFormatType const type = EFormatType::U8);

			Texture1D();

		protected:

			u32 GetTarget();

			u32 Size;
		};

		class Texture2D : public ImageTexture
		{

		public:

			void Storage(vec2u const & size, EFormatComponents const components = EFormatComponents::RGBA, EInternalFormatType const type = EInternalFormatType::U8);
			void Image(void * const data, EFormatComponents const components = EFormatComponents::RGBA, EFormatType const type = EFormatType::U8);
			void SubImage(void * const data, vec2u const & offset, vec2u const & size, EFormatComponents const components = EFormatComponents::RGBA, EFormatType const type = EFormatType::U8);

		protected:

			u32 GetTarget();

			vec2u Size;
		};

		class Texture3D : public ImageTexture
		{

		public:

			void Storage(vec3u const & size, EFormatComponents const components = EFormatComponents::RGBA, EInternalFormatType const type = EInternalFormatType::U8);
			void Image(void * const data, EFormatComponents const components = EFormatComponents::RGBA, EFormatType const type = EFormatType::U8);
			void SubImage(void * const data, vec3u const & offset, vec3u const & size, EFormatComponents const components = EFormatComponents::RGBA, EFormatType const type = EFormatType::U8);

		protected:

			u32 GetTarget();

			vec3u Size;
		};
	}
}
