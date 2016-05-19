
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

				CPipelineState(CWindow * Window);
				~CPipelineState();

				void SetProgram(SharedPointer<IShaderProgram> ShaderProgram);
				void SetVertexBuffer(uint const Index, SharedPointer<IVertexBuffer> VertexBuffer);
				void SetIndexBuffer(SharedPointer<IIndexBuffer> IndexBuffer);
				void SetUniform(string const & Name, SharedPointer<IUniform> Uniform);
				void SetTexture(string const & Name, SharedPointer<ITexture> Texture);

				void SetPrimitiveType(EPrimitiveType const PrimitiveType);
				void SetFeatureEnabled(EDrawFeature const Feature, bool const Enabled);
				void SetPolygonOffsetAmount(float const Amount);
				void SetBlendMode(EBlendMode const BlendMode);

				void OfferUniform(string const & Name, SharedPointer<IUniform> Uniform);
				void OfferTexture(string const & Name, SharedPointer<ITexture> Texture);

				void IgnoreUniform(string const & Name);

				set<string> GetUnboundUniforms() const;

				void Load();

				CWindow * Window = nullptr;

				SharedPointer<CShaderProgram> ShaderProgram;
				vector<SharedPointer<CVertexBuffer>> VertexBuffers;
				SharedPointer<CIndexBuffer> IndexBuffer;

				uint VertexArrayHandle = 0;
				bool Loaded = false;

				map<string, SharedPointer<IUniform const>> Uniforms;
				map<uint, SharedPointer<IUniform const>> BoundUniforms;

				map<string, SharedPointer<ITexture const>> Textures;
				map<u32, SharedPointer<ITexture const>> BoundTextures;

				set<string> UnboundUniforms;
				set<string> UnboundAttributes;

				bool DrawWireframe = false;
				bool CullFront = false;
				bool CullBack = false;
				bool DisableDepthTest = false;
				bool DisableDepthWrite = false;
				bool PolygonOffset = false;
				float PolygonOffsetAmount = 1.f;
				EBlendMode BlendMode = EBlendMode::None;
				uint PrimitiveType;

			};

		}
	}
}
