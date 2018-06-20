
#include "CPipelineState.h"
#include "Utilities.h"

#include <ionWindow.h>

#include <glm/gtc/type_ptr.hpp>


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			CPipelineState::CPipelineState(ID3D11Device * Device, ID3D11DeviceContext * ImmediateContext)
			{
				this->Device = Device;
				this->ImmediateContext = ImmediateContext;
			}

			void CPipelineState::SetShader(SharedPointer<IShader> inShader)
			{
				if (inShader)
				{
					Shader = std::dynamic_pointer_cast<CShader>(inShader);

					ConstantBuffers.clear();

					std::vector<ID3D11ShaderReflection *> Reflectors;

					if (Shader->VertexStage && Shader->VertexStage->Reflector)
					{
						Reflectors.push_back(Shader->VertexStage->Reflector);
					}
					if (Shader->GeometryStage && Shader->GeometryStage->Reflector)
					{
						Reflectors.push_back(Shader->GeometryStage->Reflector);
					}
					if (Shader->PixelStage && Shader->PixelStage->Reflector)
					{
						Reflectors.push_back(Shader->PixelStage->Reflector);
					}

					for (auto Reflector : Reflectors)
					{
						D3D11_SHADER_DESC ShaderDesc;
						Reflector->GetDesc(& ShaderDesc);

						for (int c = 0; c < (int) ShaderDesc.ConstantBuffers; ++ c)
						{
							SConstantBufferBinding Binding;

							auto ConstantBuffer = Reflector->GetConstantBufferByIndex(c);

							D3D11_SHADER_BUFFER_DESC BufferDesc;
							ConstantBuffer->GetDesc(& BufferDesc);

							if (ConstantBuffers.find(BufferDesc.Name) != ConstantBuffers.end())
							{
								continue;
							}

							for (int v = 0; v < (int) BufferDesc.Variables; ++ v)
							{
								auto Variable = ConstantBuffer->GetVariableByIndex(v);

								D3D11_SHADER_VARIABLE_DESC VariableDesc;
								D3D11_SHADER_TYPE_DESC TypeDesc;

								Variable->GetDesc(& VariableDesc);
								auto Type = Variable->GetType();
								Type->GetDesc(& TypeDesc);

								if (TypeDesc.Members)
								{
									if (TypeDesc.Elements)
									{
										// Array of Structs
										int ArrayOffset = 0;

										for (UINT j = 0; j < TypeDesc.Elements; ++ j)
										{
											for (UINT i = 0; i < TypeDesc.Members; ++ i)
											{
												auto Field = Type->GetMemberTypeByIndex(i);
												D3D11_SHADER_TYPE_DESC FieldDesc;
												Field->GetDesc(& FieldDesc);
												std::cout << "Struct array member: " << Type->GetMemberTypeName(i) << " at offset " << FieldDesc.Offset + ArrayOffset << std::endl;


												SUniformBinding Uniform;
												Uniform.Offset = VariableDesc.StartOffset + ArrayOffset + FieldDesc.Offset;
												Binding.Variables[string(VariableDesc.Name) + "[" + std::to_string(j) + "]" + "." + Type->GetMemberTypeName(i)] = Uniform;
											}

											ArrayOffset += VariableDesc.Size / TypeDesc.Elements;
										}
									}
									else
									{
										// Struct
										for (UINT i = 0; i < TypeDesc.Members; ++ i)
										{
											auto Field = Type->GetMemberTypeByIndex(i);
											D3D11_SHADER_TYPE_DESC FieldDesc;
											Field->GetDesc(& FieldDesc);
											std::cout << "Struct member: " << Type->GetMemberTypeName(i) << " at offset " << FieldDesc.Offset << std::endl;

											SUniformBinding Uniform;
											Uniform.Offset = VariableDesc.StartOffset + FieldDesc.Offset;
											Binding.Variables[string(VariableDesc.Name) + "." + Type->GetMemberTypeName(i)] = Uniform;
										}
									}
								}
								else
								{

									if (TypeDesc.Elements)
									{
										// Array of POD
										int ArrayOffset = 0;

										for (UINT j = 0; j < TypeDesc.Elements; ++ j)
										{
											std::cout << "Array element at offset " << ArrayOffset << std::endl;


											SUniformBinding Uniform;
											Uniform.Offset = VariableDesc.StartOffset + ArrayOffset;
											Binding.Variables[string(VariableDesc.Name) + "[" + std::to_string(j) + "]"] = Uniform;

											ArrayOffset += VariableDesc.Size / TypeDesc.Elements;
										}
									}
									else
									{
										// POD
										SUniformBinding Uniform;
										Uniform.Offset = VariableDesc.StartOffset;
										Binding.Variables[VariableDesc.Name] = Uniform;
									}
								}
							}

							D3D11_BUFFER_DESC CBDesc = {};
							CBDesc.Usage = D3D11_USAGE_DEFAULT;
							CBDesc.ByteWidth = BufferDesc.Size;
							CBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
							CheckedDXCall( Device->CreateBuffer(&CBDesc, nullptr, &Binding.ConstantBuffer) );
							Binding.Size = BufferDesc.Size;
							Binding.Slot = c;

							ConstantBuffers[BufferDesc.Name] = Binding;
						}

						for (int t = 0; t < (int) ShaderDesc.BoundResources; ++ t)
						{
							D3D11_SHADER_INPUT_BIND_DESC Desc;
							CheckedDXCall( Reflector->GetResourceBindingDesc(t, & Desc) );

							if (Desc.Type == D3D_SIT_TEXTURE)
							{
								STextureBinding Binding;
								Binding.Name = Desc.Name;
								Binding.ResourceSlot = 0;
								Binding.SamplerSlot = 0;

								TextureBindings.push_back(Binding);
							}
						}
					}


					//Textures.clear();

					//UnboundAttributes = KeySet(Shader->Attributes);
					//UnboundAttributes.erase("gl_VertexID");

					Loaded = false;
				}
			}

			void CPipelineState::SetVertexBuffer(uint const Index, SharedPointer<IVertexBuffer> inVertexBuffer)
			{
				if (Index >= VertexBuffers.size())
				{
					VertexBuffers.resize(Index + 1);
				}

				VertexBuffers[Index] = std::dynamic_pointer_cast<CVertexBuffer>(inVertexBuffer);
				// Bound VBOs are not part of VAO state

				Loaded = false;
			}

			void CPipelineState::SetIndexBuffer(SharedPointer<IIndexBuffer> inIndexBuffer)
			{
				IndexBuffer = std::dynamic_pointer_cast<CIndexBuffer>(inIndexBuffer);
			}

			void CPipelineState::OfferUniform(string const & Name, SharedPointer<IUniform> Uniform)
			{
				if (! Shader)
				{
					Log::Error("Cannot set uniforms or textures on a PipelineState with no specified shader program.");
					return;
				}

				for (auto & Buffer : ConstantBuffers)
				{
					for (auto & Variable : Buffer.second.Variables)
					{
						if (Variable.first == Name)
						{
							Variable.second.Uniform = Uniform;
							return;
						}
					}
				}
			}

			void CPipelineState::SetUniform(string const & Name, SharedPointer<IUniform> Uniform)
			{
				if (! Shader)
				{
					Log::Error("Cannot set uniforms or textures on a PipelineState with no specified shader program.");
					return;
				}

				for (auto & Buffer : ConstantBuffers)
				{
					for (auto & Variable : Buffer.second.Variables)
					{
						if (Variable.first == Name)
						{
							Variable.second.Uniform = Uniform;
							return;
						}
					}
				}

				if (Uniform)
				{
					Log::Warn("Attempting to set uniform or texture '%s' that is not required by shader, ignoring.", Name);
				}
				else
				{
					Log::Error("Attempting to remove uniform or texture '%s' that was never specified, ignoring.", Name);
				}
			}

			void CPipelineState::IgnoreUniform(string const & Name)
			{
				if (! Shader)
				{
					Log::Error("Cannot set uniforms or textures on a PipelineState with no specified shader program.");
					return;
				}

				for (auto & Buffer : ConstantBuffers)
				{
					for (auto & Variable : Buffer.second.Variables)
					{
						if (Variable.first == Name)
						{
							Variable.second.Ignored = true;
							return;
						}
					}
				}

				Log::Error("Attempting to ignore uniform or texture '%s' that was never specified, ignoring.", Name);
			}

			void CPipelineState::SetTexture(string const & Name, SharedPointer<ITexture> Texture)
			{
				if (! Shader)
				{
					Log::Error("Cannot set uniforms or textures on a PipelineState with no specified shader program.");
					return;
				}

				for (auto & TextureBinding : TextureBindings)
				{
					if (TextureBinding.Name == Name)
					{
						TextureBinding.Texture = std::dynamic_pointer_cast<CTexture>(Texture);
						return;
					}
				}

				if (Texture)
				{
					Log::Warn("Attempting to set uniform or texture '%s' that is not required by shader, ignoring.", Name);
				}
				else
				{
					Log::Error("Attempting to remove uniform or texture '%s' that was never specified, ignoring.", Name);
				}
			}

			void CPipelineState::SetPrimitiveType(EPrimitiveType const PrimitiveType)
			{
				switch (PrimitiveType)
				{
				default:
				case EPrimitiveType::Triangle:
					this->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
					break;
				case EPrimitiveType::Point:
					this->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
					break;
				case EPrimitiveType::Line:
					this->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
					break;
				case EPrimitiveType::LineStrip:
					this->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
					break;
				}
			}

			void CPipelineState::SetFeatureEnabled(EDrawFeature const Feature, bool const Enabled)
			{
				switch (Feature)
				{
				case EDrawFeature::Wireframe:
					DrawWireframe = Enabled;
					break;
				case EDrawFeature::CullFront:
					CullFront = Enabled;
					break;
				case EDrawFeature::CullBack:
					CullBack = Enabled;
					break;
				case EDrawFeature::DisableDepthTest:
					DisableDepthTest = Enabled;
					break;
				case EDrawFeature::DisableDepthWrite:
					DisableDepthWrite = Enabled;
					break;
				case EDrawFeature::PolygonOffset:
					PolygonOffset = Enabled;
					break;
				}
			}

			void CPipelineState::SetPolygonOffsetAmount(float const Amount)
			{
				PolygonOffsetAmount = Amount;
			}

			void CPipelineState::SetBlendMode(EBlendMode const BlendMode)
			{
				this->BlendMode = BlendMode;
			}

			void CPipelineState::OfferTexture(string const & Name, SharedPointer<ITexture> Texture)
			{
				if (! Shader)
				{
					Log::Error("Cannot set uniforms or textures on a PipelineState with no specified shader program.");
					return;
				}

				if (! Texture)
				{
					Log::Error("Invalid paramter to CPipelineState::OfferTexture: expected non-null Texture");
					return;
				}

				//if (UnboundUniforms.count(Name) == 1)
				//{
				//	Textures[Name] = Texture;
				//	UnboundUniforms.erase(Name);
				//}
			}

			set<string> CPipelineState::GetUnboundUniforms() const
			{
				set<string> UnboundUniforms;

				for (auto & ConstantBuffer : ConstantBuffers)
				{
					for (auto & Variable : ConstantBuffer.second.Variables)
					{
						if (! Variable.second.Uniform)
						{
							UnboundUniforms.insert(Variable.first);
						}
					}
				}

				return UnboundUniforms;
			}

			void CPipelineState::Draw()
			{
				if (! Shader || VertexBuffers.empty() || ! IndexBuffer || ! Shader->VertexStage->VertexShader || ! Shader->PixelStage->PixelShader)
				{
					Log::Error("Attempting to draw an invalid PipelineState");
					return;
				}

				UINT Stride = VertexBuffers[0]->LayoutSize;
				UINT Offset = 0;
				ImmediateContext->IASetVertexBuffers(0, 1, &VertexBuffers[0]->VertexBuffer, &Stride, &Offset);
				ImmediateContext->IASetIndexBuffer(IndexBuffer->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
				ImmediateContext->IASetInputLayout(VertexBuffers[0]->InputLayout->InputLayout);
				ImmediateContext->IASetPrimitiveTopology(PrimitiveType);

				ImmediateContext->VSSetShader(Shader->VertexStage->VertexShader, nullptr, 0);
				ImmediateContext->PSSetShader(Shader->PixelStage->PixelShader, nullptr, 0);

				int Slot = 0;
				for (auto & ConstantBuffer : ConstantBuffers)
				{
					byte * ConstantBufferData = new byte[ConstantBuffer.second.Size]();

					for (auto & Variable : ConstantBuffer.second.Variables)
					{
						if (Variable.second.Uniform)
						{
							auto Uniform = Variable.second.Uniform;
							byte * Address = ConstantBufferData + Variable.second.Offset;

							switch (Uniform->GetType())
							{
							case EUniformType::Float:
							case EUniformType::Int:
								std::memcpy(Address, Uniform->GetData(), Uniform->GetSize());
								break;

							case EUniformType::Bool:
							{
								BOOL b = * (bool *) Uniform->GetData();
								std::memcpy(Address, & b, sizeof(BOOL));
								break;
							}

							case EUniformType::Float2:
								std::memcpy(Address, static_cast<vec2f const *>(Uniform->GetData())->ValuePointer(), sizeof(float) * 2);
								break;

							case EUniformType::Float3:
								std::memcpy(Address, static_cast<vec3f const *>(Uniform->GetData())->ValuePointer(), sizeof(float) * 3);
								break;

							case EUniformType::Float4:
								std::memcpy(Address, static_cast<vec4f const *>(Uniform->GetData())->ValuePointer(), sizeof(float) * 4);
								break;

							case EUniformType::Int2:
								std::memcpy(Address, static_cast<vec2i const *>(Uniform->GetData())->ValuePointer(), sizeof(int) * 2);
								break;

							case EUniformType::Int3:
								std::memcpy(Address, static_cast<vec3i const *>(Uniform->GetData())->ValuePointer(), sizeof(int) * 3);
								break;

							case EUniformType::Int4:
								std::memcpy(Address, static_cast<vec4i const *>(Uniform->GetData())->ValuePointer(), sizeof(int) * 4);
								break;

							case EUniformType::Matrix4x4:
								std::memcpy(
									Address,
									glm::value_ptr(* static_cast<glm::mat4 const *>(Uniform->GetData())),
									sizeof(float) * 16);
								break;


							case EUniformType::FloatArray:
								std::memcpy(
									Address,
									static_cast<vector<float> const *>(Uniform->GetData())->data(),
									static_cast<vector<float> const *>(Uniform->GetData())->size() * sizeof(float));
								break;

							case EUniformType::Float2Array:
							{
								vector<float> CompactedData;
								for (auto const & Vector : *static_cast<vector<vec2f> const *>(Uniform->GetData()))
								{
									CompactedData.push_back(Vector.X);
									CompactedData.push_back(Vector.Y);
								}
								std::memcpy(
									Address,
									CompactedData.data(),
									CompactedData.size() * sizeof(float));

								break;
							}

							case EUniformType::Float3Array:
							case EUniformType::Matrix4x4Array:
								Log::Error("Unsupported uniform type during uniform binding: '%s'", GetUniformTypeString(Uniform->GetType()));
								break;

							default:
								Log::Error("Unexpected uniform type during uniform binding: '%s'", GetUniformTypeString(Uniform->GetType()));
								break;
							}

						}
						else if (! Variable.second.Ignored)
						{
							Log::Error("Uniform expected but not provided: '%s'", Variable.first);
						}
					}

					ImmediateContext->UpdateSubresource(ConstantBuffer.second.ConstantBuffer, 0, nullptr, ConstantBufferData, 0, 0);
					delete[] ConstantBufferData;

					ImmediateContext->VSSetConstantBuffers(ConstantBuffer.second.Slot, 1, &ConstantBuffer.second.ConstantBuffer);
					ImmediateContext->PSSetConstantBuffers(ConstantBuffer.second.Slot, 1, &ConstantBuffer.second.ConstantBuffer);

					Slot ++;
				}

				for (auto & TextureBinding : TextureBindings)
				{
					if (TextureBinding.Texture)
					{
						ImmediateContext->PSSetShaderResources(0, 1, & TextureBinding.Texture->ShaderResourceView);
						ImmediateContext->PSSetSamplers(0, 1, & TextureBinding.Texture->SamplerState);
					}
				}


				if (BlendMode != EBlendMode::None)
				{
					D3D11_BLEND_DESC BlendDesc = {};

					BlendDesc.RenderTarget[0].BlendEnable = true;
					BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

					if (BlendMode == EBlendMode::Alpha)
					{
						BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
						BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
						BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
					}
					else if (BlendMode == EBlendMode::Additive)
					{
						BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
						BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
						BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_SRC_ALPHA;
					}
					else if (BlendMode == EBlendMode::Min)
					{
						BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_MIN;
						BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
						BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
					}
					else if (BlendMode == EBlendMode::Max)
					{
						BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_MAX;
						BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
						BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_SRC_ALPHA;
					}

					BlendDesc.RenderTarget[0].BlendOpAlpha = BlendDesc.RenderTarget[0].BlendOp;
					BlendDesc.RenderTarget[0].SrcBlendAlpha = BlendDesc.RenderTarget[0].SrcBlend;
					BlendDesc.RenderTarget[0].DestBlendAlpha = BlendDesc.RenderTarget[0].DestBlend;

					ID3D11BlendState * BlendState = nullptr;
					Device->CreateBlendState(& BlendDesc, & BlendState);
					ImmediateContext->OMSetBlendState(BlendState, NULL, 0xffffffff);
					BlendState->Release();
				}

				ImmediateContext->DrawIndexed(IndexBuffer->Size, 0, 0);

				if (BlendMode != EBlendMode::None)
				{
					ImmediateContext->OMSetBlendState(NULL, NULL, 0xffffffff);
				}
			}

		}
	}
}
