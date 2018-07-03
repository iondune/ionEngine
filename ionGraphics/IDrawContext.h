
#pragma once

#include <ionCore.h>

#include "IShader.h"
#include "IPipelineState.h"


namespace ion
{
	namespace Graphics
	{

		//! \brief Alternative to Pipeline State rendering. Represents the context for one or many draw calls.
		//! \ingroup ionGraphics
		class IDrawContext
		{

		public:

			virtual ~IDrawContext()
			{}

			virtual void SetShader(SharedPointer<IShader> ShaderProgram) = 0;

			virtual void SetInputLayout(IInputLayout * InputLayout) = 0;
			virtual void SetVertexBuffer(SharedPointer<IVertexBuffer> VertexBuffer) = 0;
			virtual void SetInstanceBuffer(SharedPointer<IInstanceBuffer> InstanceBuffer) = 0;
			virtual void SetIndexBuffer(SharedPointer<IIndexBuffer> IndexBuffer) = 0;

			virtual void SetConstantBuffer(IConstantBuffer * ConstantBuffer) = 0;
			virtual void SetTexture(string const & Name, SharedPointer<ITexture> Texture) = 0;

			virtual void SetPrimitiveType(EPrimitiveType const PrimitiveType) = 0;
			virtual void SetFeatureEnabled(EDrawFeature const Feature, bool const Enabled) = 0;
			virtual void SetBlendMode(EBlendMode const BlendMode) = 0;

			virtual void Draw() = 0;

		};

	}
}
