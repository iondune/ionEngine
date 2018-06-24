
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>

#include <d3d11.h>
#include <dxgi.h>

#include "CVertexStage.h"
#include "CGeometryStage.h"
#include "CPixelStage.h"


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			class CShader : public IShader
			{
			public:

				void SetVertexStage(SharedPointer<IVertexStage> VertexShader);
				void SetGeometryStage(SharedPointer<IGeometryStage> GeometryShader);
				void SetPixelStage(SharedPointer<IPixelStage> PixelShader);

				void Link();

				struct SUniform
				{
					string Name;
					EUniformType Type;
					int Offset = 0;

					bool operator == (SUniform const & Other) const
					{
						return Name == Other.Name && Type == Other.Type && Offset == Other.Offset;
					}
				};

				struct SConstantBuffer
				{
					vector<SUniform> Variables;
					string Name;
					int Size = 0;
					int Slot = 0;
					int Stages = 0;

					bool Equivalent(SConstantBuffer const & Other) const
					{
						return Variables == Other.Variables;
					}
				};

				void ReflectInputElements();
				void ReflectConstantBuffers();
				void ReflectConstantBuffersStage(ID3D11ShaderReflection * Reflector, int const Stage);
				void ReflectConstantBufferVariables(vector<SUniform> & Uniforms, ID3D11ShaderReflectionType * Type, string const & Name, int const Offset);

				SharedPointer<CVertexStage> VertexStage;
				SharedPointer<CGeometryStage> GeometryStage;
				SharedPointer<CPixelStage> PixelStage;

				bool Linked = false;
				vector<SInputLayoutElement> InputElements;
				vector<SConstantBuffer> ConstantBuffers;

			};

		}
	}
}
