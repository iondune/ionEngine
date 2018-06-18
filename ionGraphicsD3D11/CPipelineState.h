
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>

#include "CShaderProgram.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CTexture.h"


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{
			
			class CPipelineState : public IPipelineState
			{

			public:

				CPipelineState(ID3D11Device * Device, ID3D11DeviceContext * ImmediateContext);

				void SetShader(SharedPointer<IShader> Shader);
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

				void Load() {}
				void Draw();

				ID3D11Device * Device = nullptr;
				ID3D11DeviceContext * ImmediateContext = nullptr;

				SharedPointer<CShader> Shader;
				vector<SharedPointer<CVertexBuffer>> VertexBuffers;
				SharedPointer<CIndexBuffer> IndexBuffer;

				uint VertexArrayHandle = 0;
				bool Loaded = false;


				struct SUniformBinding
				{
					int Offset = 0;
					SharedPointer<IUniform const> Uniform;
				};

				struct SConstantBufferBinding
				{
					map<string, SUniformBinding> Variables;
					ID3D11Buffer * ConstantBuffer = nullptr;
					int Size = 0;
				};

				struct STextureBinding
				{
					string Name;
					int ResourceSlot = 0;
					int SamplerSlot = 0;
					EShaderType RequiredBy;
					SharedPointer<CTexture const> Texture;
				};

				map<string, SConstantBufferBinding> ConstantBuffers; 
				map<string, SharedPointer<IUniform const>> Uniform;

				vector<STextureBinding> TextureBindings;
				map<string, SharedPointer<ITexture const>> Textures;

				set<string> UnboundAttributes;

				bool DrawWireframe = false;
				bool CullFront = false;
				bool CullBack = false;
				bool DisableDepthTest = false;
				bool DisableDepthWrite = false;
				bool PolygonOffset = false;
				float PolygonOffsetAmount = 1.f;
				EBlendMode BlendMode = EBlendMode::None;
				D3D_PRIMITIVE_TOPOLOGY PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

			};

		}
	}
}
