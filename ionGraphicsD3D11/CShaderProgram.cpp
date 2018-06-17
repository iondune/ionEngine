
#include "CShaderProgram.h"
#include "Utilities.h"


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			void CShader::SetVertexStage(SharedPointer<IVertexStage> VertexShader)
			{
				VertexStage = std::dynamic_pointer_cast<CVertexStage>(VertexShader);
			}

			void CShader::SetGeometryStage(SharedPointer<IGeometryStage> GeometryShader)
			{
				GeometryStage = std::dynamic_pointer_cast<CGeometryStage>(GeometryShader);
			}

			void CShader::SetPixelStage(SharedPointer<IPixelStage> PixelShader)
			{
				PixelStage = std::dynamic_pointer_cast<CPixelStage>(PixelShader);
			}

			void CShader::Link()
			{
			}

		}
	}
}
