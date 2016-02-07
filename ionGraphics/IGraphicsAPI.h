
#pragma once

#include <ionCore.h>
#include <ionWindow.h>


namespace ion
{
	namespace Graphics
	{

		enum class EValueType
		{
			Error         = 0,
			Float         = 1,
			Float2        = 2,
			Float3        = 3,
			Float4        = 4,
			Matrix4x4     = 5,
			Double        = 6,
			SignedInt8    = 7,
			SignedInt16   = 8,
			SignedInt32   = 9,
			UnsignedInt8  = 10,
			UnsignedInt16 = 11,
			UnsignedInt32 = 12,
		};

		enum class EScalarType
		{
			Error         = 0,
			Float         = 1,
			Double        = 2,
			SignedInt8    = 3,
			SignedInt16   = 4,
			SignedInt32   = 5,
			UnsignedInt8  = 6,
			UnsignedInt16 = 7,
			UnsignedInt32 = 8,
		};

		size_t GetValueTypeSize(EValueType const ValueType);

		class IVertexShader
		{

		public:

			virtual ~IVertexShader() {}

		};

		class IPixelShader
		{

		public:

			virtual ~IPixelShader() {}

		};

		class IShaderProgram
		{

		public:

			virtual void SetVertexStage(IVertexShader * VertexShader) = 0;
			virtual void SetPixelStage(IPixelShader * PixelShader) = 0;

		};

		struct SInputLayoutElement
		{
			string Name = "";
			int Components = 1;
			EValueType Type = EValueType::Float;

			SInputLayoutElement(string const & Name, int const Components, EValueType const Type)
			{
				this->Name = Name;
				this->Components = Components;
				this->Type = Type;
			}
		};

		class IVertexBuffer
		{

		public:

			virtual ~IVertexBuffer() {}
			virtual void SetInputLayout(SInputLayoutElement * InputLayout, int const NumElements) = 0;

		};

		class IIndexBuffer
		{

		public:

			virtual ~IIndexBuffer() {}

		};

		class IUniform
		{

		public:

			virtual void const * GetData() const = 0;
			virtual EValueType GetType() const = 0;
			virtual size_t GetSize() const = 0;

		};

		template <typename T>
		class IUniformTyped : public IUniform
		{

		public:

			EValueType GetType() const;

			size_t GetSize() const
			{
				return sizeof(T);
			}

		};


		template <typename T>
		class CUniformReference : public IUniformTyped<T>
		{

		public:

			T const * Value;

			CUniformReference()
				: Value(0)
			{}

			CUniformReference(T const * value)
				: Value(value)
			{}

			CUniformReference(T const & value)
				: Value(& value)
			{}

			void const * GetData() const
			{
				return Value;
			}

		};

		template <typename T>
		class CUniformValue : public IUniformTyped<T>
		{

		public:

			T Value;

			CUniformValue()
			{}

			CUniformValue(T const & value)
				: Value(value)
			{}

			void const * GetData() const
			{
				return & Value;
			}

			CUniformValue & operator = (T const & value)
			{
				Value = value;
				return * this;
			}

			operator T() const
			{
				return Value;
			}

		};

		class ITexture
		{
		public:

			////////////////////
			// Texture Params //
			////////////////////

			enum class EFilter
			{
				Nearest = 0,
				Linear  = 1,
			};

			enum class EWrapMode
			{
				Clamp  = 0,
				Mirror = 1,
				Repeat = 2,
			};

			enum class EFormatComponents
			{
				R    = 0,
				RG   = 1,
				RGB  = 2,
				RGBA = 3,
			};
			
			enum class EInternalFormatType
			{
				Fix8  = 0,
				Fix16 = 1,
				U8    = 2,
				U16   = 3,
				U32   = 4,
				S8    = 5,
				S16   = 6,
				S32   = 7,
				F16   = 8,
				F32   = 9,
			};

			enum class EMipMaps
			{
				False = 0,
				True  = 1,
			};

			//! Sets the minimizing filter for this texture
			//! Default is EFilter::Linear
			virtual ITexture * SetMinFilter(EFilter const MinFilter) = 0;

			//! Sets the maximizing filter for this texture
			//! Default is EFilter::Linear
			virtual ITexture * SetMagFilter(EFilter const MagFilter) = 0;

			//! Sets the mip map filter for this texture
			//! Default is EFilter::Linear
			virtual ITexture * SetMipMapFilter(EFilter const MipMapFilter) = 0;

			//! Sets the wrap mode for this texture
			//! Default is EWrapMode::Repeat
			virtual ITexture * SetWrapMode(EWrapMode const WrapMode) = 0;

			//! Sets the anisotropy filtering value for this texture
			//! A value < 0 indicates that the max anisotrophy value should be used
			//! Default is -1
			virtual ITexture * SetAnisotropy(f32 const Anisotropy) = 0;

			virtual EFilter GetMinFilter() = 0;
			virtual EFilter GetMagFilter() = 0;
			virtual EFilter GetMipMapFilter() = 0;
			virtual EWrapMode GetWrapMode() = 0;
			virtual f32 GetAnisotropy() = 0;

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

		class IPipelineState
		{

		public:

			virtual void SetProgram(IShaderProgram * ShaderProgram) = 0;
			virtual void SetVertexBuffer(IVertexBuffer * VertexBuffer) = 0;
			virtual void SetIndexBuffer(IIndexBuffer * IndexBuffer) = 0;
			virtual void SetUniform(string const & Name, IUniform * Uniform) = 0;
			virtual void SetTexture(string const & Name, ITexture * Texture) = 0;

			virtual void OfferUniform(string const & Name, IUniform * Uniform) = 0;

			virtual uint GetUnboundUniformCount() const = 0;
			virtual string GetUnboundUniform(uint const Index) const = 0;

			virtual void Load() = 0;

		};

		class IRenderTarget
		{

		public:

			virtual void ClearColor() = 0;
			virtual void ClearDepth() = 0;
			virtual void ClearColorAndDepth() = 0;

			virtual void SetClearColor(color3f const & Color) = 0;

		};

		class IGraphicsAPI
		{

		public:

			virtual IVertexShader * CreateVertexShaderFromFile(string const & FileName) = 0;
			virtual IPixelShader * CreatePixelShaderFromFile(string const & FileName) = 0;
			virtual IVertexShader * CreateVertexShaderFromSource(string const & Source) = 0;
			virtual IPixelShader * CreatePixelShaderFromSource(string const & Source) = 0;

			virtual IShaderProgram * CreateShaderProgram() = 0;

			virtual IVertexBuffer * CreateVertexBuffer(float const * const Data, size_t const Elements) = 0;
			virtual IIndexBuffer * CreateIndexBuffer(void const * Data, size_t const Elements, EValueType const ValueType) = 0;

			virtual ITexture2D * CreateTexture2D(vec2u const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type) = 0;
			virtual ITexture3D * CreateTexture3D(vec3u const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type) = 0;

			virtual IPipelineState * CreatePipelineState() = 0;

			virtual IRenderTarget * GetWindowBackBuffer(CWindow * Window) = 0;

			virtual void Draw(IPipelineState * State) = 0;

		};
	}
}
