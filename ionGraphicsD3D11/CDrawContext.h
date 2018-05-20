
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

			class CDrawContext;

			class CDrawConfig : public IDrawConfig
			{

				friend class CDrawContext;

			public:

				virtual void SetVertexBuffer(uint const Index, SharedPointer<IVertexBuffer> VertexBuffer);
				virtual void SetIndexBuffer(SharedPointer<IIndexBuffer> IndexBuffer);
				virtual void SetUniform(string const & Name, SharedPointer<IUniform> Uniform);
				virtual void SetTexture(string const & Name, SharedPointer<ITexture> Texture);
				virtual void SetInstanceCount(uint const Count);

			protected:

				vector<SharedPointer<CVertexBuffer>> VertexBuffers;
				SharedPointer<CIndexBuffer> IndexBuffer;
				SharedPointer<CIndexBuffer> UsedIndexBuffer;

				struct SUniformBinding
				{
					string Name;
					int Handle = -1;
					SharedPointer<IUniform const> Uniform;
				};

				struct STextureBinding
				{
					string Name;
					int Handle = -1;
					SharedPointer<ITexture const> Texture;
				};

				map<string, SUniformBinding *> ProvidedUniforms;
				map<string, STextureBinding *> ProvidedTextures;

				vector<SUniformBinding *> UniformBindings;
				vector<STextureBinding *> TextureBindings;

				set<string> RequiredUniforms;
				set<string> UnboundAttributes;

				uint VertexArrayHandle = 0;

				bool NeedsToBeLoaded = true;
				bool LoadedSuccessfully = false;

				uint InstanceCount = 0;

				CDrawContext * Container = nullptr;

			};

			class CDrawContext : public IDrawContext
			{

			public:

				CDrawContext();

				virtual void SetShader(SharedPointer<IShader> Shader);
				virtual void SetVertexBuffer(uint const Index, SharedPointer<IVertexBuffer> VertexBuffer);
				virtual void SetIndexBuffer(SharedPointer<IIndexBuffer> IndexBuffer);
				virtual void SetUniform(string const & Name, SharedPointer<IUniform> Uniform);
				virtual void SetTexture(string const & Name, SharedPointer<ITexture> Texture);

				virtual void SetPrimitiveType(EPrimitiveType const PrimitiveType);
				virtual void SetFeatureEnabled(EDrawFeature const Feature, bool const Enabled);
				virtual void SetBlendMode(EBlendMode const BlendMode);
				virtual void SetInstancingEnabled(bool const Enabled);

				virtual set<string> GetUnboundUniforms() const;

				virtual void Draw(IDrawConfig * DrawConfig);
				virtual IDrawConfig * CreateDrawConfig();

				static void Invalidate();

			protected:

				SharedPointer<CShader> Shader;

				vector<SharedPointer<CVertexBuffer>> VertexBuffers;
				SharedPointer<CIndexBuffer> IndexBuffer;

				map<string, SharedPointer<IUniform const>> Uniforms;
				map<string, SharedPointer<ITexture const>> Textures;

				map<uint, SharedPointer<IUniform const>> BoundUniforms;
				map<uint, SharedPointer<ITexture const>> BoundTextures;

				set<string> RequiredUniforms;
				set<string> UnboundAttributes;

				bool DrawWireframe = false;
				bool CullFront = false;
				bool CullBack = false;
				bool DisableDepthTest = false;
				bool DisableDepthWrite = false;
				uint PrimitiveType;
				EBlendMode BlendMode = EBlendMode::None;
				bool UseInstancing = false;

				vector<CDrawConfig *> Configs;

				int StartTextures = 0;

				void LoadConfig(CDrawConfig * DrawConfig);
				void LoadVertexBuffer(CDrawConfig * DrawConfig, SharedPointer<CVertexBuffer> VertexBuffer);

				void InternalBindUniform(uint const Handle, SharedPointer<IUniform const> const Uniform);

				bool InternalDrawSetup();
				void InternalDrawTeardown();

				static CDrawContext * CurrentContext;

			};
		}
	}
}
