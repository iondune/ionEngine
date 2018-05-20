
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

				SharedPointer<CVertexStage> VertexStage;
				SharedPointer<CGeometryStage> GeometryStage;
				SharedPointer<CPixelStage> PixelStage;

			};

		}
	}
}
