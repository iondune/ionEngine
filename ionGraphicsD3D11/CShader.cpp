
#include "CShader.h"
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
				if (VertexStage && VertexStage->Reflector)
				{
					auto Reflector = VertexStage->Reflector;

					D3D11_SHADER_DESC ShaderDesc;
					Reflector->GetDesc(& ShaderDesc);

					for (int i = 0; i < (int) ShaderDesc.InputParameters; ++ i)
					{
						D3D11_SIGNATURE_PARAMETER_DESC ParameterDesc;
						CheckedDXCall( Reflector->GetInputParameterDesc(i, & ParameterDesc) );

						if (ParameterDesc.SemanticIndex > 0)
						{
							Log::Warn("Semantic index greater than zero not supported for input layout: %s%d", ParameterDesc.SemanticName, ParameterDesc.SemanticIndex);
						}

						int Components = 1;
						switch (ParameterDesc.Mask)
						{
						case 1:
							Components = 1;
							break;
						case 3:
							Components = 2;
							break;
						case 7:
							Components = 3;
							break;
						case 15:
							Components = 4;
							break;
						default:
							Log::Error("Unexpected input layout mask: %u", ParameterDesc.Mask);
							break;
						}

						EAttributeType Type;
						switch (ParameterDesc.ComponentType)
						{
						case D3D_REGISTER_COMPONENT_UINT32:
							Type = EAttributeType::UnsignedInt;
							break;
						case D3D_REGISTER_COMPONENT_SINT32:
							Type = EAttributeType::Int;
							break;
						case D3D_REGISTER_COMPONENT_FLOAT32:
							Type = EAttributeType::Float;
							break;
						default:
							Log::Error("Unexpected input layout type: %u", ParameterDesc.ComponentType);
							break;
						}

						InputElements.push_back(SInputLayoutElement(
							ParameterDesc.SemanticName,
							Components,
							Type
						));
					}
				}

				Linked = true;
			}

		}
	}
}
