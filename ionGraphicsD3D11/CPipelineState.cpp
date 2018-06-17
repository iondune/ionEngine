
#include "CPipelineState.h"
#include <ionWindow.h>


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

							for (int v = 0; v < (int) BufferDesc.Variables; ++ v)
							{
								auto Variable = ConstantBuffer->GetVariableByIndex(v);
								D3D11_SHADER_VARIABLE_DESC VariableDesc;
								Variable->GetDesc(& VariableDesc);

								SUniformBinding Uniform;
								Uniform.Offset = VariableDesc.StartOffset;
								Binding.Variables[VariableDesc.Name] = Uniform;
							}

							D3D11_BUFFER_DESC CBDesc = {};
							CBDesc.Usage = D3D11_USAGE_DEFAULT;
							CBDesc.ByteWidth = sizeof(BufferDesc.Size);
							CBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
							assert(S_OK == Device->CreateBuffer(&CBDesc, nullptr, &Binding.ConstantBuffer));
							Binding.Size = BufferDesc.Size;

							ConstantBuffers.push_back(Binding);
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

			void CPipelineState::SetUniform(string const & Name, SharedPointer<IUniform> Uniform)
			{
				if (! Shader)
				{
					Log::Error("Cannot set uniforms or textures on a PipelineState with no specified shader program.");
					return;
				}

				for (auto & Buffer : ConstantBuffers)
				{
					for (auto & Variable : Buffer.Variables)
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

			void CPipelineState::SetTexture(string const & Name, SharedPointer<ITexture> Texture)
			{
				if (! Shader)
				{
					Log::Error("Cannot set uniforms or textures on a PipelineState with no specified shader program.");
					return;
				}

				//if (Texture)
				//{
				//	if (UnboundUniforms.count(Name) == 1)
				//	{
				//		Textures[Name] = Texture;
				//		UnboundUniforms.erase(Name);
				//	}
				//	else if (Textures.find(Name) != Textures.end())
				//	{
				//		Textures[Name] = Texture;
				//	}
				//	else
				//	{
				//		Log::Warn("Attempting to set uniform or texture '%s' that is not required by shader, ignoring.", Name);
				//	}
				//}
				//else
				//{
				//	if (Textures.erase(Name) == 1)
				//	{
				//		UnboundUniforms.insert(Name);
				//	}
				//	else
				//	{
				//		Log::Error("Attempting to remove uniform or texture '%s' that was never specified, ignoring.", Name);
				//	}
				//}
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

			void CPipelineState::OfferUniform(string const & Name, SharedPointer<IUniform> Uniform)
			{
				SetUniform(Name, Uniform);
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

			void CPipelineState::IgnoreUniform(string const & Name)
			{
			}

			set<string> CPipelineState::GetUnboundUniforms() const
			{
				return set<string>();
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
					byte * ConstantBufferData = new byte[ConstantBuffer.Size]();

					int Offset = 0;
					for (auto & Variable : ConstantBuffer.Variables)
					{
						std::memcpy(ConstantBufferData + Offset, Variable.second.Uniform->GetData(), Variable.second.Uniform->GetSize());
					}

					ImmediateContext->UpdateSubresource(ConstantBuffer.ConstantBuffer, 0, nullptr, ConstantBufferData, 0, 0);
					delete[] ConstantBufferData;

					ImmediateContext->VSSetConstantBuffers(Slot, 1, &ConstantBuffer.ConstantBuffer);
					ImmediateContext->PSSetConstantBuffers(Slot, 1, &ConstantBuffer.ConstantBuffer);

					Slot ++;
				}

				ImmediateContext->DrawIndexed(IndexBuffer->Size, 0, 0);
			}

		}
	}
}
