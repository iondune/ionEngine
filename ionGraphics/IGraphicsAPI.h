
#pragma once

#include <ionCore.h>
#include <ionWindow.h>


namespace ion
{
	namespace Graphics
	{

		enum class EValueType
		{
			Float,
			Float2,
			Float3,
			Float4,
			Matrix4x4,
			Double,
			SignedInt8,
			SignedInt16,
			SignedInt32,
			UnsignedInt8,
			UnsignedInt16,
			UnsignedInt32,
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

		class IShaderProgram
		{

		public:

			virtual void SetVertexStage(IVertexShader * VertexShader) = 0;
			virtual void SetPixelStage(IPixelShader * PixelShader) = 0;
			virtual void SetInputLayout(SInputLayoutElement * InputLayout, int const NumElements) = 0;

		};

		class IVertexBuffer
		{

		public:

			virtual ~IVertexBuffer() {}

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

		class IPipelineState
		{

		public:

			virtual void SetProgram(IShaderProgram * ShaderProgram) = 0;
			virtual void SetVertexBuffer(IVertexBuffer * VertexBuffer) = 0;
			virtual void SetIndexBuffer(IIndexBuffer * IndexBuffer) = 0;
			virtual void SetUniform(string const & Name, IUniform * Uniform) = 0;

			virtual void Load() = 0;

		};

		class IRenderTarget
		{

		public:

			virtual void ClearColor() = 0;
			virtual void ClearDepth() = 0;
			virtual void ClearColorAndDepth() = 0;

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
			virtual IPipelineState * CreatePipelineState() = 0;

			virtual IRenderTarget * GetWindowBackBuffer(CWindow * Window) = 0;

			virtual void Draw(IPipelineState * State) = 0;

		};
	}
}
