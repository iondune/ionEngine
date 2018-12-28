
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

			class CShader : public IShader
			{
			public:

				void SetVertexStage(SharedPointer<IVertexStage> VertexShader);
				void SetGeometryStage(SharedPointer<IGeometryStage> GeometryShader);
				void SetPixelStage(SharedPointer<IPixelStage> PixelShader);

				void Link();


				uint Handle = 0;
				bool Linked = false;

				map<string, pair<uint, uint>> Attributes;
				map<string, uint> Uniforms;
			
			};
		}
	}
}
