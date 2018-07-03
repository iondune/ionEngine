
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>

#include <d3d11.h>
#include <dxgi.h>

#include "CShader.h"


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{
			
			class CConstantBuffer : public IConstantBuffer
			{

			public:

				CConstantBuffer(ID3D11Device * Device, ID3D11DeviceContext * ImmediateContext, CShader::SConstantBuffer const & inDescriptor);

				void SetUniform(string const & Name, SharedPointer<IUniform> Uniform);
				bool OfferUniform(string const & Name, SharedPointer<IUniform> Uniform);

				void Synchronize();

				ID3D11DeviceContext * ImmediateContext = nullptr;

				CShader::SConstantBuffer Descriptor;
				ID3D11Buffer * ConstantBuffer = nullptr;

				struct SUniformBinding
				{
					string Name;
					int Offset = 0;
					EUniformType Type = EUniformType::Unknown;
					SharedPointer<IUniform const> Uniform;
					bool Ignored = false;
				};

				vector<SUniformBinding> UniformBindings;

			};

		}
	}
}
