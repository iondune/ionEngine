
#pragma once

#include <ionCore.h>


namespace ion
{
	namespace Graphics
	{

		enum class EValueType
		{
			Float,
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

		class IPipelineState
		{

		public:

			virtual void SetProgram(IShaderProgram * ShaderProgram) = 0;
			virtual void SetVertexBuffer(IVertexBuffer * VertexBuffer) = 0;
			virtual void SetIndexBuffer(IIndexBuffer * IndexBuffer) = 0;

		};

		class IRenderTarget
		{

		public:

			virtual void ClearColor();
			virtual void ClearDepth();

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

			virtual void Draw(IPipelineState * State) = 0;

		};
	}
}
