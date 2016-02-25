
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>

#include "CShaderProgram.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{
			
			class CPipelineState : public IPipelineState
			{

			public:

				~CPipelineState();

				void SetProgram(SharedPtr<IShaderProgram> ShaderProgram);
				void SetVertexBuffer(uint const Index, SharedPtr<IVertexBuffer> VertexBuffer);
				void SetIndexBuffer(SharedPtr<IIndexBuffer> IndexBuffer);
				void SetUniform(string const & Name, SharedPtr<IUniform> Uniform);
				void SetTexture(string const & Name, SharedPtr<ITexture> Texture);
				void SetFeatureEnabled(EDrawFeature const Feature, bool const Enabled);
				void SetBlendMode(EBlendMode const BlendMode);

				void OfferUniform(string const & Name, SharedPtr<IUniform> Uniform);
				set<string> GetUnboundUniforms() const;

				void Load();

				SharedPtr<CShaderProgram> ShaderProgram;
				vector<SharedPtr<CVertexBuffer>> VertexBuffers;
				SharedPtr<CIndexBuffer> IndexBuffer;

				uint VertexArrayHandle = 0;
				bool Loaded = false;

				map<string, SharedPtr<IUniform const>> Uniforms;
				map<uint, SharedPtr<IUniform const>> BoundUniforms;

				map<string, SharedPtr<ITexture const>> Textures;
				map<u32, SharedPtr<ITexture const>> BoundTextures;

				set<string> UnboundUniforms;
				set<string> UnboundAttributes;

				bool DrawWireframe = false;
				bool CullFront = false;
				bool CullBack = false;
				bool DisableDepthTest = false;
				bool DisableDepthWrite = false;
				EBlendMode BlendMode = EBlendMode::None;

			};

		}
	}
}
