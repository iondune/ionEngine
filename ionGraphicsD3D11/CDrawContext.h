
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>

#include "CShader.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			class CDrawContext : public IDrawContext
			{

			public:

				CDrawContext(ID3D11Device * Device, ID3D11DeviceContext * ImmediateContext);

				virtual void SetShader(SharedPointer<IShader> Shader);

				virtual void SetInputLayout(IInputLayout * InputLayout);
				virtual void SetVertexBuffer(SharedPointer<IVertexBuffer> VertexBuffer);
				virtual void SetInstanceBuffer(SharedPointer<IInstanceBuffer> InstanceBuffer);
				virtual void SetIndexBuffer(SharedPointer<IIndexBuffer> IndexBuffer);

				virtual void SetConstantBuffer(IConstantBuffer * ConstantBuffer);
				virtual void SetTexture(string const & Name, SharedPointer<ITexture> Texture);

				virtual void SetPrimitiveType(EPrimitiveType const PrimitiveType);
				virtual void SetFeatureEnabled(EDrawFeature const Feature, bool const Enabled);
				virtual void SetBlendMode(EBlendMode const BlendMode);

				virtual void Draw();
				virtual void Invalidate();

			protected:

				ID3D11Device * Device = nullptr;
				ID3D11DeviceContext * ImmediateContext = nullptr;


				struct STextureBinding
				{
					string Name;
					int ResourceSlot = 0;
					int SamplerSlot = 0;
					int Stages = 0;
				};
				map<string, STextureBinding> TextureBindings;


				SharedPointer<CShader> Shader;

				SharedPointer<CInstanceBuffer> InstanceBuffer;
				SharedPointer<CIndexBuffer> IndexBuffer;

			};
		}
	}
}
