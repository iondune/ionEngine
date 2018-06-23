
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
				ReflectInputElements();
				ReflectConstantBuffers();

				Linked = true;
			}

			void CShader::ReflectInputElements()
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
							Log::Error("Unexpected input layout mask: 0x%x", ParameterDesc.Mask);
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
			}

			void CShader::ReflectConstantBuffers()
			{
				if (VertexStage && VertexStage->Reflector)
				{
					ReflectConstantBuffersStage(VertexStage->Reflector, EShaderType::Vertex);
				}
				if (GeometryStage && GeometryStage->Reflector)
				{
					ReflectConstantBuffersStage(GeometryStage->Reflector, EShaderType::Geometry);
				}
				if (PixelStage && PixelStage->Reflector)
				{
					ReflectConstantBuffersStage(PixelStage->Reflector, EShaderType::Pixel);
				}
			}

			void CShader::ReflectConstantBuffersStage(ID3D11ShaderReflection * Reflector, int const Stage)
			{
				D3D11_SHADER_DESC ShaderDesc;
				Reflector->GetDesc(& ShaderDesc);

				for (int c = 0; c < (int) ShaderDesc.ConstantBuffers; ++ c)
				{
					ID3D11ShaderReflectionConstantBuffer * ConstantBuffer = Reflector->GetConstantBufferByIndex(c);

					D3D11_SHADER_BUFFER_DESC BufferDesc;
					ConstantBuffer->GetDesc(& BufferDesc);

					SConstantBuffer Description;
					Description.Name = BufferDesc.Name;
					Description.Stages = Stage;

					for (int v = 0; v < (int) BufferDesc.Variables; ++ v)
					{
						ID3D11ShaderReflectionVariable * Variable = ConstantBuffer->GetVariableByIndex(v);

						D3D11_SHADER_VARIABLE_DESC VariableDesc;
						Variable->GetDesc(& VariableDesc);

						Description.Size += ReflectConstantBufferVariables(Description.Variables, Variable->GetType(), VariableDesc.Name, VariableDesc.StartOffset);
					}
					Description.Size = BufferDesc.Size;

					Description.Slot = -1;
					for (int r = 0; r < (int) ShaderDesc.BoundResources; ++ r)
					{
						D3D11_SHADER_INPUT_BIND_DESC ResourceDesc;
						Reflector->GetResourceBindingDesc(r, & ResourceDesc);

						if (ResourceDesc.Type == D3D_SIT_CBUFFER)
						{
							if (string(ResourceDesc.Name) == string(BufferDesc.Name))
							{
								Description.Slot = ResourceDesc.BindPoint;
								break;
							}
						}
					}

					if (Description.Slot == -1)
					{
						Log::Error("Couldn't find bind point for constant buffer %d: '%s'", c, BufferDesc.Name);
					}

					bool ExistedPreviously = false;

					for (SConstantBuffer & Buffer : ConstantBuffers)
					{
						if (Buffer.Equivalent(Description))
						{
							if (Buffer.Slot != Description.Slot)
							{
								Log::Error("Constant buffer is different bind slots between shader stages: '%s'", Description.Name);
							}

							Buffer.Stages |= Stage;
							ExistedPreviously = true;
							break;
						}
					}

					if (! ExistedPreviously)
					{
						ConstantBuffers.push_back(Description);
					}
				}
			}

			int CShader::ReflectConstantBufferVariables(vector<SUniform> & Uniforms, ID3D11ShaderReflectionType * Type, string const & Name, int const Offset)
			{
				int Size = 0;

				D3D11_SHADER_TYPE_DESC TypeDesc;
				Type->GetDesc(& TypeDesc);

				if (TypeDesc.Members)
				{
					if (TypeDesc.Elements)
					{
						// Array of Structs

						for (UINT j = 0; j < TypeDesc.Elements; ++ j)
						{
							int StructSize = 0;

							for (UINT i = 0; i < TypeDesc.Members; ++ i)
							{
								StructSize += ReflectConstantBufferVariables(
									Uniforms,
									Type->GetMemberTypeByIndex(i),
									Name + "[" + std::to_string(j) + "]" + "." + Type->GetMemberTypeName(i),
									Offset + Size);
							}

							Size += StructSize;
						}
					}
					else
					{
						// Struct

						for (UINT i = 0; i < TypeDesc.Members; ++ i)
						{
							Size += ReflectConstantBufferVariables(
								Uniforms,
								Type->GetMemberTypeByIndex(i),
								Name + "." + Type->GetMemberTypeName(i),
								Offset);
						}
					}
				}
				else
				{
					if (TypeDesc.Elements)
					{
						// Array

						for (UINT j = 0; j < TypeDesc.Elements; ++ j)
						{
							Size += ReflectConstantBufferUniform(Uniforms, TypeDesc, Name + "[" + std::to_string(j) + "]", Offset + Size);
						}

					}
					else
					{
						// Variable

						Size = ReflectConstantBufferUniform(Uniforms, TypeDesc, Name, Offset);
					}
				}

				return Size;
			}

			int CShader::ReflectConstantBufferUniform(vector<SUniform> & Uniforms, D3D11_SHADER_TYPE_DESC const & TypeDesc, string const & Name, int const Offset)
			{
				int Size = 0;

				SUniform Uniform;
				Uniform.Offset = Offset + TypeDesc.Offset;
				Uniform.Name = Name;

				switch (TypeDesc.Class)
				{
				case D3D_SVC_SCALAR:
					switch (TypeDesc.Type)
					{
					case D3D_SVT_INT:
						Uniform.Type = EUniformType::Int;
						Size = 4;
						break;
					case D3D_SVT_FLOAT:
						Uniform.Type = EUniformType::Float;
						Size = 4;
						break;
					case D3D_SVT_BOOL:
						Uniform.Type = EUniformType::Bool;
						Size = 4;
						break;
					default:
						Log::Error("Unsupported shader variable scalar type: %d", TypeDesc.Type);
						break;
					}
					break;

				case D3D_SVC_VECTOR:
					switch (TypeDesc.Type)
					{
					case D3D_SVT_INT:
						Uniform.Type = EUniformType::Int;
						Size = 4 * 4;
						break;
					case D3D_SVT_FLOAT:
						Uniform.Type = EUniformType::Float;
						Size = 4 * 4;
						break;
					default:
						Log::Error("Unsupported shader variable vector type: %d", TypeDesc.Type);
						break;
					}

					Uniform.Type = (EUniformType) ((int) Uniform.Type + (TypeDesc.Columns - 1));

					break;

				case D3D_SVC_MATRIX_COLUMNS:
					if (TypeDesc.Type == D3D_SVT_FLOAT)
					{
						if (TypeDesc.Rows != TypeDesc.Columns)
						{
							Log::Error("Unsupported shader variable matrix not square: %dx%d", TypeDesc.Rows, TypeDesc.Columns);
						}
						else
						{
							if (TypeDesc.Rows == 4)
							{
								Uniform.Type = EUniformType::Matrix4x4;
								Size = 16 * 4;
							}
							else
							{
								Log::Error("Unsupported shader variable matrix size: %dx%d", TypeDesc.Rows, TypeDesc.Columns);
							}
						}
					}
					else
					{
						Log::Error("Unsupported shader variable matrix type: %d", TypeDesc.Type);
					}
					break;

				default:
					Log::Error("Unsupported shader variable class: %d", TypeDesc.Class);
					break;
				}

				Uniforms.push_back(Uniform);
				return Size;
			}

		}
	}
}
