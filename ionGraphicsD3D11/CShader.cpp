
#include "CShader.h"
#include "CInputLayout.h"
#include "CConstantBuffer.h"
#include "Utilities.h"


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			CShader::CShader(ID3D11Device * Device, ID3D11DeviceContext * ImmediateContext)
			{
				this->Device = Device;
				this->ImmediateContext = ImmediateContext;
			}

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

			IConstantBuffer * CShader::GetConstantBuffer(string const & Name)
			{
				IConstantBuffer * ConstantBuffer = nullptr;

				if (! Linked)
				{
					Link();
				}

				for (SConstantBuffer const & Desc : ConstantBuffers)
				{
					if (Desc.Name == Name)
					{
						ConstantBuffer = new CConstantBuffer(Device, ImmediateContext, Desc);
						break;
					}
				}

				return ConstantBuffer;
			}

			IInputLayout * CShader::CreateInputLayout(vector<SInputBufferLayout> const & Buffers)
			{
				CInputLayout * InputLayout = new CInputLayout();

				vector<D3D11_INPUT_ELEMENT_DESC> Layout;
				D3D11_INPUT_ELEMENT_DESC Desc;

				for (SInputBufferLayout const & Buffer : Buffers)
				{
					Desc.InputSlot = Buffer.Slot;
					Desc.InputSlotClass = (Buffer.Instanced ? D3D11_INPUT_PER_INSTANCE_DATA : D3D11_INPUT_PER_VERTEX_DATA);

					int ByteAlignment = 0;

					for (SInputLayoutElement const & Element : Buffer.LayoutElements)
					{
						Desc.SemanticName = Element.Name.c_str();
						Desc.SemanticIndex = 0;
						Desc.InstanceDataStepRate = 0;

						static DXGI_FORMAT const Lookup[4][4] =
						{
							{ DXGI_FORMAT_R32_FLOAT, DXGI_FORMAT_R32G32_FLOAT, DXGI_FORMAT_R32G32B32_FLOAT, DXGI_FORMAT_R32G32B32A32_FLOAT },
							{ DXGI_FORMAT_R32_SINT,  DXGI_FORMAT_R32G32_SINT,  DXGI_FORMAT_R32G32B32_SINT,  DXGI_FORMAT_R32G32B32A32_SINT  },
							{ DXGI_FORMAT_R32_UINT,  DXGI_FORMAT_R32G32_UINT,  DXGI_FORMAT_R32G32B32_UINT,  DXGI_FORMAT_R32G32B32A32_UINT  },
							{ DXGI_FORMAT_R32_FLOAT, DXGI_FORMAT_R32G32_FLOAT, DXGI_FORMAT_R32G32B32_FLOAT, DXGI_FORMAT_R32G32B32A32_FLOAT },
						};

						if (Element.Type == EAttributeType::Double)
						{
							Log::Warn("InputLayout double types not supported.");
						}

						Desc.Format = Lookup[(int) Element.Type][Element.Components - 1];
						Desc.AlignedByteOffset = ByteAlignment;

						ByteAlignment += 4 * Element.Components;

						Layout.push_back(Desc);
					} // Element : Buffer.LayoutElements
				} // Buffer : Buffers

				CheckedDXCall( Device->CreateInputLayout(
					Layout.data(),
					(UINT) Layout.size(),
					VertexStage->CompileBlob->GetBufferPointer(),
					VertexStage->CompileBlob->GetBufferSize(),
					& InputLayout->InputLayout) );
				
				return InputLayout;
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

						ReflectConstantBufferVariables(Description.Variables, Variable->GetType(), VariableDesc.Name, VariableDesc.StartOffset);
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

			void CShader::ReflectConstantBufferVariables(vector<SUniform> & Uniforms, ID3D11ShaderReflectionType * Type, string const & Name, int const Offset)
			{
				D3D11_SHADER_TYPE_DESC TypeDesc;
				Type->GetDesc(& TypeDesc);

				if (TypeDesc.Members)
				{
					if (TypeDesc.Elements)
					{
						// Array of Structs
						int ArrayOffset = 0;

						for (UINT j = 0; j < TypeDesc.Elements; ++ j)
						{
							int StructSize = 0;

							for (UINT i = 0; i < TypeDesc.Members; ++ i)
							{
								ID3D11ShaderReflectionType * Field = Type->GetMemberTypeByIndex(i);
								D3D11_SHADER_TYPE_DESC FieldDesc;
								Field->GetDesc(& FieldDesc);

								SUniform Uniform;
								Uniform.Type = GetUniformType(FieldDesc);
								Uniform.Offset = Offset + ArrayOffset + FieldDesc.Offset;
								Uniform.Name = Name + "[" + std::to_string(j) + "]" + "." + Type->GetMemberTypeName(i);
								Uniforms.push_back(Uniform);

								StructSize = RoundUp(FieldDesc.Offset + 4 * FieldDesc.Columns, 16); 
							}

							ArrayOffset += StructSize;
						}
					}
					else
					{
						// Struct
						for (UINT i = 0; i < TypeDesc.Members; ++ i)
						{
							ID3D11ShaderReflectionType * Field = Type->GetMemberTypeByIndex(i);
							D3D11_SHADER_TYPE_DESC FieldDesc;
							Field->GetDesc(& FieldDesc);

							SUniform Uniform;
							Uniform.Type = GetUniformType(FieldDesc);
							Uniform.Offset = Offset + FieldDesc.Offset;
							Uniform.Name = Name + "." + Type->GetMemberTypeName(i);
							Uniforms.push_back(Uniform);
						}
					}
				}
				else
				{
					// POD or Array of POD

					SUniform Uniform;
					Uniform.Type = GetUniformType(TypeDesc);

					if (TypeDesc.Elements)
					{
						// Array of POD
						int ArrayOffset = 0;

						for (UINT j = 0; j < TypeDesc.Elements; ++ j)
						{
							Uniform.Offset = Offset + ArrayOffset;
							Uniform.Name = Name + "[" + std::to_string(j) + "]";
							Uniforms.push_back(Uniform);

							ArrayOffset += 4;
						}
					}
					else
					{
						// POD
						Uniform.Offset = Offset;
						Uniform.Name = Name;
						Uniforms.push_back(Uniform);
					}
				}
			}

			EUniformType CShader::GetUniformType(D3D11_SHADER_TYPE_DESC const & TypeDesc)
			{
				EUniformType UniformType = EUniformType::Unknown;

				switch (TypeDesc.Type)
				{
				case D3D_SVT_INT:
					UniformType = (EUniformType) ((int) EUniformType::Int + (TypeDesc.Columns - 1));
					break;
				case D3D_SVT_FLOAT:
					if (TypeDesc.Rows == 4)
					{
						if (TypeDesc.Columns == 4)
						{
							UniformType = EUniformType::Matrix4x4;
						}
						else
						{
							Log::Error("Found matrix uniform with other than 4x4 size: %dx%d", TypeDesc.Rows, TypeDesc.Columns);
						}
					}
					else if (TypeDesc.Rows == 1)
					{
						if (TypeDesc.Columns <= 4)
						{
							UniformType = (EUniformType) ((int) EUniformType::Float + (TypeDesc.Columns - 1));
						}
						else
						{
							Log::Error("Found float vector uniform with unexpected size: %dx%d", TypeDesc.Rows, TypeDesc.Columns);
						}
					}
					else
					{
						Log::Error("Found float uniform with unexpected size: %dx%d", TypeDesc.Rows, TypeDesc.Columns);
					}
					break;
				case D3D_SVT_BOOL:
					UniformType = EUniformType::Bool;
					if (TypeDesc.Columns != 1)
					{
						Log::Error("Vectors of bools not supported as uniforms");
					}
					break;
				case D3D_SVT_UINT:
					UniformType = EUniformType::UnsignedInt;
					if (TypeDesc.Columns != 1)
					{
						Log::Error("Vectors of unsigned ints not supported as uniforms");
					}
					break;
				default:
					Log::Error("Unsupported shader variable type: %d", TypeDesc.Type);
					break;
				}

				return UniformType;
			}

		}
	}
}
