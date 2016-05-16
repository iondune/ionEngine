
#pragma once

#include <ionCore.h>

#include "IShaderProgram.h"
#include "IVertexBuffer.h"
#include "IIndexBuffer.h"
#include "IUniform.h"
#include "ITexture.h"


namespace ion
{
	namespace Graphics
	{

		enum class EDrawFeature
		{
			Wireframe = 0,
			CullFront = 1,
			CullBack = 2,
			DisableDepthTest = 3,
			DisableDepthWrite = 4,
			PolygonOffsetForward = 5,
			PolygonOffsetBackward = 6
		};

		enum class EBlendMode
		{
			None = 0,
			Alpha = 1,
			Additive = 2
		};

		enum class EPrimitiveType
		{
			Triangle = 0,
			Line = 1,
			LineStrip = 2,
			Point = 3
		};

		class IPipelineState
		{

		public:

			virtual ~IPipelineState()
			{}

			virtual void SetProgram(SharedPointer<IShaderProgram> ShaderProgram) = 0;
			virtual void SetVertexBuffer(uint const Index, SharedPointer<IVertexBuffer> VertexBuffer) = 0;
			virtual void SetIndexBuffer(SharedPointer<IIndexBuffer> IndexBuffer) = 0;
			virtual void SetUniform(string const & Name, SharedPointer<IUniform> Uniform) = 0;
			virtual void SetTexture(string const & Name, SharedPointer<ITexture> Texture) = 0;

			virtual void OfferUniform(string const & Name, SharedPointer<IUniform> Uniform) = 0;
			virtual void OfferTexture(string const & Name, SharedPointer<ITexture> Texture) = 0;

			virtual void IgnoreUniform(string const & Name) = 0;

			virtual void SetPrimitiveType(EPrimitiveType const PrimitiveType) = 0;
			virtual void SetFeatureEnabled(EDrawFeature const Feature, bool const Enabled) = 0;
			virtual void SetBlendMode(EBlendMode const BlendMode) = 0;

			virtual set<string> GetUnboundUniforms() const = 0;

			virtual void Load() = 0;

		};

	}
}
