#pragma once

#include <ionCore.h>
#include <ionMath.h>


namespace ion
{
	namespace GL
	{
		/////////////
		// Buffers //
		/////////////

		class Buffer
		{
			friend class VertexArray;

		public:

			enum class EAccessFrequency
			{
				Stream = 0,
				Static = 1,
				Dynamic = 2
			};

			enum class EAccessNature
			{
				Draw = 0,
				Read = 1,
				Copy = 2
			};

			void Data(u32 const size, void const * const data,
				EAccessFrequency const accessFrequency = EAccessFrequency::Stream,
				EAccessNature const accessNature = EAccessNature::Draw);

			void SubData(u32 const size, u32 const offset, void const * const data);

			void Delete();
			~Buffer();

		protected:

			Buffer();

			void Bind();
			void Unbind();
			virtual u32 GetTarget() = 0;

			u32 Handle;
		};

		class VertexBuffer : public Buffer
		{
		protected:

			u32 GetTarget();
		};

		class IndexBuffer : Buffer
		{
		protected:

			u32 GetTarget();
		};
		

		///////////////////
		// Vertex Arrays //
		///////////////////

		enum class EFormatType
		{
			U8 = 0,
			U16 = 1,
			U32 = 2,
			S8 = 3,
			S16 = 4,
			S32 = 5,
			F32 = 6
		};

		class Util
		{
		public:

			static u32 const TypeMatrix[7];
		};

		class VertexArray
		{
		public:

			VertexArray();

			void AttributePointer(VertexBuffer * Buffer, u32 const index, u32 const size, EFormatType const type, u32 const stride = 0, void * offset = 0);

			void EnableAttribute(u32 const index);
			void DisableAttribute(u32 const index);
			
			void Delete();
			~VertexArray();

		protected:
			
			u32 Handle;
		};


		//////////////
		// Textures //
		//////////////

		class Texture
		{
		public:
			
			void Delete();
			~Texture();

		protected:

			Texture();
			
			u32 Handle;
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
			void Storage(vec2u const & size, EFormatComponents const components = EFormatComponents::RGBA, EInternalFormatType const type = EInternalFormatType::U8);
			void Image(void * const data, EFormatComponents const components = EFormatComponents::RGBA, EFormatType const type = EFormatType::U8);
			void SubImage(void * const data, vec2u const & offset, vec2u const & size, EFormatComponents const components = EFormatComponents::RGBA, EFormatType const type = EFormatType::U8);

		protected:

			u32 GetTarget();

			vec2u Size;
		};

		class Texture3D : public ImageTexture
		{
			void Storage(vec3u const & size, EFormatComponents const components = EFormatComponents::RGBA, EInternalFormatType const type = EInternalFormatType::U8);
			void Image(void * const data, EFormatComponents const components = EFormatComponents::RGBA, EFormatType const type = EFormatType::U8);
			void SubImage(void * const data, vec3u const & offset, vec3u const & size, EFormatComponents const components = EFormatComponents::RGBA, EFormatType const type = EFormatType::U8);

		protected:

			u32 GetTarget();

			vec3u Size;
		};


		////////////
		// Shader //
		////////////

		class Shader
		{
		public:

			void Source(std::vector<std::string> const & Source);
			void Source(std::string const & Source);

			bool Compile();

			void Delete();
			~Shader();

		protected:

			Shader(u32 const handle);

			u32 const Handle;
		};

		class ComputeShader : public Shader
		{
		public:

			ComputeShader();
		};

		class VertexShader : public Shader
		{
		public:

			VertexShader();
		};

		class TesselationControlShader : public Shader
		{
		public:

			TesselationControlShader();
		};

		class TesselationEvaluationShader : public Shader
		{
		public:

			TesselationEvaluationShader();
		};

		class GeometryShader : public Shader
		{
		public:

			GeometryShader();
		};

		class FragmentShader : public Shader
		{
		public:

			FragmentShader();
		};


		/////////////
		// Program //
		/////////////

		class Program
		{
		public:

			class Attribute
			{
			public:

				//! Attribute is automatically enabled by any operation
				void Enable();

				void BindBuffer(VertexBuffer * buffer, u32 const elementSize);
			};

			class Uniform
			{
			public:

			};

			void AttachShader(Shader * shader);
			bool Link();

			std::vector<Attribute> const & GetActiveAttributes();
			std::vector<Uniform> const & GetActiveUniforms();

		private:

			std::vector<Attribute> Attributes;
			std::vector<Uniform> Uniforms;
		};
	}
}
