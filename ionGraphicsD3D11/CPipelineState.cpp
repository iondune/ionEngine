
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
					Loaded = false;

					Shader = std::dynamic_pointer_cast<CShader>(inShader);

					if (! Shader->Linked)
					{
						Shader->Link();

						if (! Shader->Linked)
						{
							Log::Error("Cannot initialize PipelineState - shader could not be linked.");
							Shader = nullptr;
							return;
						}
					}

					ConstantBuffers.clear();

					for (CShader::SConstantBuffer const & Buffer : Shader->ConstantBuffers)
					{
						SConstantBufferBinding BufferBinding;

						D3D11_BUFFER_DESC ConstantBufferDesc = {};
						ConstantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
						ConstantBufferDesc.ByteWidth = Buffer.Size;
						ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
						CheckedDXCall( Device->CreateBuffer(& ConstantBufferDesc, nullptr, & BufferBinding.ConstantBuffer) );

						BufferBinding.Size = Buffer.Size;
						BufferBinding.Slot = Buffer.Slot;

						for (CShader::SUniform const & Uniform : Buffer.Variables)
						{
							SUniformBinding UniformBinding;
							UniformBinding.Offset = Uniform.Offset;
							BufferBinding.Variables[Uniform.Name] = UniformBinding;
						}

						ConstantBuffers[Buffer.Name] = BufferBinding;
					}

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

						for (int t = 0; t < (int) ShaderDesc.BoundResources; ++ t)
						{
							D3D11_SHADER_INPUT_BIND_DESC Desc;
							CheckedDXCall( Reflector->GetResourceBindingDesc(t, & Desc) );

							if (Desc.Type == D3D_SIT_TEXTURE)
							{
								STextureBinding Binding;
								Binding.Name = Desc.Name;
								Binding.ResourceSlot = Desc.BindPoint;
								Binding.SamplerSlot = Desc.BindPoint;

								TextureBindings[Desc.Name] = (Binding);
							}
						}
					}
				}
			}

			void CPipelineState::SetVertexBuffer(uint const Index, SharedPointer<IVertexBuffer> inVertexBuffer)
			{
				if (Index >= VertexBuffers.size())
				{
					VertexBuffers.resize(Index + 1);
				}

				Loaded = false;

				VertexBuffers[Index] = std::dynamic_pointer_cast<CVertexBuffer>(inVertexBuffer);
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

			void CPipelineState::OfferTexture(string const & Name, SharedPointer<ITexture> Texture)
			{
				if (! Shader)
				{
					Log::Error("Cannot set uniforms or textures on a PipelineState with no specified shader program.");
					return;
				}

				for (auto & TextureBinding : TextureBindings)
				{
					if (TextureBinding.second.Name == Name)
					{
						TextureBinding.second.Texture = std::dynamic_pointer_cast<CTexture>(Texture);
						return;
					}
				}
			}

			void CPipelineState::SetTexture(string const & Name, SharedPointer<ITexture> Texture)
			{
				if (! Shader)
				{
					Log::Error("Cannot set uniforms or textures on a PipelineState with no specified shader program.");
					return;
				}

				for (auto & [Key, TextureBinding] : TextureBindings)
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

			void CPipelineState::Load()
			{
				if (Loaded)
				{
					return;
				}

				if (! Shader)
				{
					Log::Error("Cannot load an invalid PipelineState - no shader.");
					return;
				}

				if (Shader->InputElements.size() == 0)
				{
					Log::Error("Cannot load an invalid PipelineState - shader has no input stages.");
					return;
				}

				if (! Shader->VertexStage->VertexShader)
				{
					Log::Error("Cannot load an invalid PipelineState - shader has no vertex stage.");
					return;
				}

				if (! Shader->PixelStage->PixelShader)
				{
					Log::Error("Cannot load an invalid PipelineState - shader has no pixel stage.");
					return;
				}

				if (VertexBuffers.empty())
				{
					Log::Error("Cannot load an invalid PipelineState - no vertex buffers.");
					return;
				}

				if (! IndexBuffer)
				{
					Log::Error("Cannot load an invalid PipelineState - no index buffer.");
					return;
				}

				vector<D3D11_INPUT_ELEMENT_DESC> Layout;

				for (SInputLayoutElement const & InputElement : Shader->InputElements)
				{
					bool FoundMatch = false;
					int Slot = 0;

					for (std::shared_ptr<CVertexBuffer> VertexBuffer : VertexBuffers)
					{
						int Offset = 0;

						for (SInputLayoutElement const & VertexElement : VertexBuffer->InputLayoutElements)
						{
							if (InputElement.Name == VertexElement.Name)
							{
								if (InputElement.Type != VertexElement.Type)
								{
									Log::Error("Shader expects input of type '%s', vertex buffer provided '%s' for slot '%s.",
										GetAttributeTypeString(InputElement.Type),
										GetAttributeTypeString(VertexElement.Type),
										InputElement.Name
									);
								}

								if (InputElement.Components != VertexElement.Components)
								{
									Log::Error("Shader expects input with %d elements, vertex buffer provided %d for slot '%s.",
										InputElement.Components,
										VertexElement.Components,
										InputElement.Name
									);
								}

								D3D11_INPUT_ELEMENT_DESC Desc;
								Desc.SemanticName = VertexElement.Name.c_str();
								Desc.SemanticIndex = 0;
								Desc.InputSlot = Slot;
								Desc.InputSlotClass = (VertexBuffer->Instancing ? D3D11_INPUT_PER_INSTANCE_DATA : D3D11_INPUT_PER_VERTEX_DATA);
								Desc.InstanceDataStepRate = (VertexBuffer->Instancing ? 1 : 0);

								static DXGI_FORMAT const Lookup[4][4] =
								{
									{ DXGI_FORMAT_R32_FLOAT, DXGI_FORMAT_R32G32_FLOAT, DXGI_FORMAT_R32G32B32_FLOAT, DXGI_FORMAT_R32G32B32A32_FLOAT },
									{ DXGI_FORMAT_R32_SINT,  DXGI_FORMAT_R32G32_SINT,  DXGI_FORMAT_R32G32B32_SINT,  DXGI_FORMAT_R32G32B32A32_SINT  },
									{ DXGI_FORMAT_R32_UINT,  DXGI_FORMAT_R32G32_UINT,  DXGI_FORMAT_R32G32B32_UINT,  DXGI_FORMAT_R32G32B32A32_UINT  },
									{ DXGI_FORMAT_R32_FLOAT, DXGI_FORMAT_R32G32_FLOAT, DXGI_FORMAT_R32G32B32_FLOAT, DXGI_FORMAT_R32G32B32A32_FLOAT },
								};

								Desc.Format = Lookup[(int) VertexElement.Type][VertexElement.Components - 1];
								Desc.AlignedByteOffset = Offset;

								Layout.push_back(Desc);
								FoundMatch = true;
								break;
							}

							Offset += 4 * VertexElement.Components;
						} // VertexBuffer->InputLayoutElements

						Slot ++;

						if (FoundMatch)
						{
							break;
						}
					} // VertexBuffers

					if (! FoundMatch)
					{
						Log::Error("Shader expected layout element '%s', not provided by vertex buffers.", InputElement.Name);
					}
				} // Shader->InputElements

				CheckedDXCall( Device->CreateInputLayout(
					Layout.data(),
					(UINT) Layout.size(),
					Shader->VertexStage->CompileBlob->GetBufferPointer(),
					(SIZE_T) Shader->VertexStage->CompileBlob->GetBufferSize(),
					& InputLayout) );

				Loaded = true;
			}

			void CPipelineState::Draw(bool const Instancing, int const InstanceCount)
			{
				if (! Loaded)
				{
					return;
				}

				vector<ID3D11Buffer *> Buffers;
				vector<UINT> Strides;
				vector<UINT> Offsets;

				for (auto & VertexBuffer : VertexBuffers)
				{
					Buffers.push_back(VertexBuffer->VertexBuffer);
					Strides.push_back(VertexBuffer->LayoutSize);
					Offsets.push_back(0);
				}

				ImmediateContext->IASetVertexBuffers(0, (UINT) VertexBuffers.size(), Buffers.data(), Strides.data(), Offsets.data());
				ImmediateContext->IASetIndexBuffer(IndexBuffer->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
				ImmediateContext->IASetInputLayout(InputLayout);
				ImmediateContext->IASetPrimitiveTopology(PrimitiveType);

				ImmediateContext->VSSetShader(Shader->VertexStage ? Shader->VertexStage->VertexShader : nullptr, nullptr, 0);
				ImmediateContext->GSSetShader(Shader->GeometryStage ? Shader->GeometryStage->GeometryShader : nullptr, nullptr, 0);
				ImmediateContext->PSSetShader(Shader->PixelStage ? Shader->PixelStage->PixelShader : nullptr, nullptr, 0);

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
							case EUniformType::UnsignedInt:
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
					ImmediateContext->GSSetConstantBuffers(ConstantBuffer.second.Slot, 1, &ConstantBuffer.second.ConstantBuffer);
					ImmediateContext->PSSetConstantBuffers(ConstantBuffer.second.Slot, 1, &ConstantBuffer.second.ConstantBuffer);

					Slot ++;
				}

				for (auto & [Key, TextureBinding] : TextureBindings)
				{
					if (TextureBinding.Texture)
					{
						int const TextureSlot = TextureBinding.ResourceSlot;

						ImmediateContext->VSSetShaderResources(TextureSlot, 1, & TextureBinding.Texture->ShaderResourceView);
						ImmediateContext->VSSetSamplers(       TextureSlot, 1, & TextureBinding.Texture->SamplerState);
						ImmediateContext->GSSetShaderResources(TextureSlot, 1, & TextureBinding.Texture->ShaderResourceView);
						ImmediateContext->GSSetSamplers(       TextureSlot, 1, & TextureBinding.Texture->SamplerState);
						ImmediateContext->PSSetShaderResources(TextureSlot, 1, & TextureBinding.Texture->ShaderResourceView);
						ImmediateContext->PSSetSamplers(       TextureSlot, 1, & TextureBinding.Texture->SamplerState);
					}
					else
					{
						Log::Error("Required texture is not bound: '%s'", TextureBinding.Name);
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

				if (Instancing)
				{
					ImmediateContext->DrawIndexedInstanced(IndexBuffer->Size, InstanceCount, 0, 0, 0);
				}
				else
				{
					ImmediateContext->DrawIndexed(IndexBuffer->Size, 0, 0);
				}

				for (auto & [Key, TextureBinding] : TextureBindings)
				{
					if (TextureBinding.Texture)
					{
						int const TextureSlot = TextureBinding.ResourceSlot;

						ID3D11ShaderResourceView * ClearTexture = nullptr;
						ID3D11SamplerState * ClearSampler = nullptr;

						ImmediateContext->VSSetShaderResources(TextureSlot, 1, & ClearTexture);
						ImmediateContext->VSSetSamplers(       TextureSlot, 1, & ClearSampler);
						ImmediateContext->GSSetShaderResources(TextureSlot, 1, & ClearTexture);
						ImmediateContext->GSSetSamplers(       TextureSlot, 1, & ClearSampler);
						ImmediateContext->PSSetShaderResources(TextureSlot, 1, & ClearTexture);
						ImmediateContext->PSSetSamplers(       TextureSlot, 1, & ClearSampler);
					}
				}

				if (BlendMode != EBlendMode::None)
				{
					ImmediateContext->OMSetBlendState(NULL, NULL, 0xffffffff);
				}
			}

		}
	}
}
