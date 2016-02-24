
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

				void SetVertexStage(SharedPtr<IVertexShader> VertexShader);
				void SetPixelStage(SharedPtr<IPixelShader> PixelShader);

				void Link();


				uint Handle = 0;
				bool Linked = false;

				map<string, pair<uint, uint>> Attributes;
				map<string, uint> Uniforms;
			
			};
		}
	}
}
