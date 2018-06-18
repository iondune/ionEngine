
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>

#include <D3D11.h>


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			enum EShaderType
			{
				Pixel,
				Vertex,
				Geometry
			};

			class CShaderStage
			{

			public:


				ID3DBlob * CompileShaderBlob(string const & Source, EShaderType const & ShaderType);
				
			};

		}
	}
}