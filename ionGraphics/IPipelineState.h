
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
			Blend = 5
		};

		class IPipelineState
		{

		public:

			virtual ~IPipelineState()
			{}

			virtual void SetProgram(SharedPtr<IShaderProgram> ShaderProgram) = 0;
			virtual void SetVertexBuffer(SharedPtr<IVertexBuffer> VertexBuffer) = 0;
			virtual void SetIndexBuffer(SharedPtr<IIndexBuffer> IndexBuffer) = 0;
			virtual void SetUniform(string const & Name, SharedPtr<IUniform> Uniform) = 0;
			virtual void SetTexture(string const & Name, SharedPtr<ITexture> Texture) = 0;

			virtual void OfferUniform(string const & Name, SharedPtr<IUniform> Uniform) = 0;

			virtual void SetFeatureEnabled(EDrawFeature const Feature, bool const Enabled) = 0;

			virtual set<string> GetUnboundUniforms() const = 0;

			virtual void Load() = 0;

		};

	}
}
