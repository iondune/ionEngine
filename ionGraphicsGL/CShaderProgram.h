
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{

			class CShaderProgram : public IShaderProgram
			{
			public:

				void SetVertexStage(IVertexShader * VertexShader);
				void SetPixelStage(IPixelShader * PixelShader);
				void SetInputLayout(SInputLayoutElement * InputLayout, int const NumElements);

				uint Handle = 0;
				bool Linked = false;
				vector<SInputLayoutElement> InputLayout;

				void Link();

				map<string, uint> Attributes;
				map<string, uint> Uniforms;
			
			};
		}
	}
}