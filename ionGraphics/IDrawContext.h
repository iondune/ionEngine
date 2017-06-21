
#pragma once

#include <ionCore.h>

#include "IPipelineState.h"


namespace ion
{
	namespace Graphics
	{

		class IDrawConfig
		{

		public:

			virtual ~IDrawConfig()
			{}

			virtual void SetVertexBuffer(uint const Index, SharedPointer<IVertexBuffer> VertexBuffer) = 0;
			virtual void SetIndexBuffer(SharedPointer<IIndexBuffer> IndexBuffer) = 0;
			virtual void SetUniform(string const & Name, SharedPointer<IUniform> Uniform) = 0;
			virtual void SetTexture(string const & Name, SharedPointer<ITexture> Texture) = 0;
			virtual void SetInstanceCount(uint const Count) = 0;

		};

		class IDrawContext
		{

		public:

			virtual ~IDrawContext()
			{}

			virtual void SetProgram(SharedPointer<IShaderProgram> ShaderProgram) = 0;
			virtual void SetVertexBuffer(uint const Index, SharedPointer<IVertexBuffer> VertexBuffer) = 0;
			virtual void SetIndexBuffer(SharedPointer<IIndexBuffer> IndexBuffer) = 0;
			virtual void SetUniform(string const & Name, SharedPointer<IUniform> Uniform) = 0;
			virtual void SetTexture(string const & Name, SharedPointer<ITexture> Texture) = 0;

			virtual void SetPrimitiveType(EPrimitiveType const PrimitiveType) = 0;
			virtual void SetFeatureEnabled(EDrawFeature const Feature, bool const Enabled) = 0;
			virtual void SetBlendMode(EBlendMode const BlendMode) = 0;
			virtual void SetInstancingEnabled(bool const Enabled) = 0;

			virtual set<string> GetUnboundUniforms() const = 0;

			virtual void Draw(IDrawConfig * DrawConfig) = 0;
			virtual IDrawConfig * CreateDrawConfig() = 0;

		};

	}
}
