
#include "CDrawContext.h"
#include "CInputLayout.h"
#include "CConstantBuffer.h"
#include "CTexture.h"


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			CDrawContext::CDrawContext(ID3D11Device * Device, ID3D11DeviceContext * ImmediateContext)
			{
				this->Device = Device;
				this->ImmediateContext = ImmediateContext;
			}

			void CDrawContext::SetShader(SharedPointer<IShader> inShader)
			{
				Invalidate();

				if (inShader)
				{
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

					std::vector<std::pair<ID3D11ShaderReflection *, int>> Reflectors;

					if (Shader->VertexStage && Shader->VertexStage->Reflector)
					{
						Reflectors.push_back(std::make_pair(Shader->VertexStage->Reflector, EShaderType::Vertex));
					}
					if (Shader->GeometryStage && Shader->GeometryStage->Reflector)
					{
						Reflectors.push_back(std::make_pair(Shader->GeometryStage->Reflector, EShaderType::Geometry));
					}
					if (Shader->PixelStage && Shader->PixelStage->Reflector)
					{
						Reflectors.push_back(std::make_pair(Shader->PixelStage->Reflector, EShaderType::Pixel));
					}

					for (auto & [Reflector, Stage] : Reflectors)
					{
						D3D11_SHADER_DESC ShaderDesc;
						Reflector->GetDesc(& ShaderDesc);

						for (int t = 0; t < (int) ShaderDesc.BoundResources; ++ t)
						{
							D3D11_SHADER_INPUT_BIND_DESC Desc;
							CheckedDXCall( Reflector->GetResourceBindingDesc(t, & Desc) );

							if (Desc.Type == D3D_SIT_TEXTURE)
							{
								auto it = TextureBindings.find(Desc.Name);
								if (it != TextureBindings.end())
								{
									it->second.Stages |= Stage;
								}
								else
								{
									STextureBinding Binding;
									Binding.Name = Desc.Name;
									Binding.ResourceSlot = Desc.BindPoint;
									Binding.SamplerSlot = Desc.BindPoint;
									Binding.Stages |= Stage;

									TextureBindings[Desc.Name] = Binding;
								}
							}
						}
					}

					ImmediateContext->VSSetShader(Shader->VertexStage   ? Shader->VertexStage->VertexShader     : nullptr, nullptr, 0);
					ImmediateContext->GSSetShader(Shader->GeometryStage ? Shader->GeometryStage->GeometryShader : nullptr, nullptr, 0);
					ImmediateContext->PSSetShader(Shader->PixelStage    ? Shader->PixelStage->PixelShader       : nullptr, nullptr, 0);
				}
			}

			void CDrawContext::SetInputLayout(IInputLayout * inInputLayout)
			{
				CInputLayout * InputLayout = dynamic_cast<CInputLayout *>(inInputLayout);

				ImmediateContext->IASetInputLayout(InputLayout->InputLayout);
			}

			void CDrawContext::SetVertexBuffer(SharedPointer<IVertexBuffer> inVertexBuffer)
			{
				std::shared_ptr<CVertexBuffer> VertexBuffer = std::dynamic_pointer_cast<CVertexBuffer>(inVertexBuffer);

				if (VertexBuffer)
				{
					UINT const Stride = VertexBuffer->LayoutSize;
					UINT const Offset = 0;
					ImmediateContext->IASetVertexBuffers(0, 1, & VertexBuffer->VertexBuffer, & Stride, & Offset);
				}
			}

			void CDrawContext::SetInstanceBuffer(SharedPointer<IInstanceBuffer> inInstanceBuffer)
			{
				InstanceBuffer = std::dynamic_pointer_cast<CInstanceBuffer>(inInstanceBuffer);

				if (InstanceBuffer)
				{
					UINT const Stride = InstanceBuffer->LayoutSize;
					UINT const Offset = 0;
					ImmediateContext->IASetVertexBuffers(1, 1, & InstanceBuffer->Buffer, & Stride, & Offset);
				}
			}

			void CDrawContext::SetIndexBuffer(SharedPointer<IIndexBuffer> inIndexBuffer)
			{
				IndexBuffer = std::dynamic_pointer_cast<CIndexBuffer>(inIndexBuffer);
				ImmediateContext->IASetIndexBuffer(IndexBuffer->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
			}

			void CDrawContext::SetConstantBuffer(IConstantBuffer * inConstantBuffer)
			{
				CConstantBuffer * ConstantBuffer = dynamic_cast<CConstantBuffer *>(inConstantBuffer);

				ImmediateContext->VSSetConstantBuffers(ConstantBuffer->Descriptor.Slot, 1, & ConstantBuffer->ConstantBuffer);
				ImmediateContext->GSSetConstantBuffers(ConstantBuffer->Descriptor.Slot, 1, & ConstantBuffer->ConstantBuffer);
				ImmediateContext->PSSetConstantBuffers(ConstantBuffer->Descriptor.Slot, 1, & ConstantBuffer->ConstantBuffer);
			}

			void CDrawContext::SetTexture(string const & Name, SharedPointer<ITexture> inTexture)
			{
				auto Texture = std::dynamic_pointer_cast<CTexture>(inTexture);

				auto it = TextureBindings.find(Name);

				if (it != TextureBindings.end())
				{
					auto const & TextureBinding = it->second;

					if (TextureBinding.Stages & EShaderType::Vertex)
					{
						ImmediateContext->VSSetShaderResources(TextureBinding.ResourceSlot, 1, & Texture->ShaderResourceView);
						ImmediateContext->VSSetSamplers(        TextureBinding.SamplerSlot, 1, & Texture->SamplerState);
					}
					if (TextureBinding.Stages & EShaderType::Geometry)
					{
						ImmediateContext->GSSetShaderResources(TextureBinding.ResourceSlot, 1, & Texture->ShaderResourceView);
						ImmediateContext->GSSetSamplers(        TextureBinding.SamplerSlot, 1, & Texture->SamplerState);
					}
					if (TextureBinding.Stages & EShaderType::Pixel)
					{
						ImmediateContext->PSSetShaderResources(TextureBinding.ResourceSlot, 1, & Texture->ShaderResourceView);
						ImmediateContext->PSSetSamplers(        TextureBinding.SamplerSlot, 1, & Texture->SamplerState);
					}
				}
			}

			void CDrawContext::SetPrimitiveType(EPrimitiveType const PrimitiveType)
			{
				switch (PrimitiveType)
				{
				default:
				case EPrimitiveType::Triangle:
					ImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
					break;
				case EPrimitiveType::Point:
					ImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
					break;
				case EPrimitiveType::Line:
					ImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
					break;
				case EPrimitiveType::LineStrip:
					ImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
					break;
				}
			}

			void CDrawContext::SetFeatureEnabled(EDrawFeature const Feature, bool const Enabled)
			{
			}

			void CDrawContext::SetBlendMode(EBlendMode const BlendMode)
			{
				if (BlendMode == EBlendMode::None)
				{
					ImmediateContext->OMSetBlendState(NULL, NULL, 0xffffffff);
				}
				else
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
			}

			void CDrawContext::Draw()
			{
				if (InstanceBuffer)
				{
					ImmediateContext->DrawIndexedInstanced(IndexBuffer->Size, InstanceBuffer->InstanceCount, 0, 0, 0);
				}
				else
				{
					ImmediateContext->DrawIndexed(IndexBuffer->Size, 0, 0);
				}
			}

			void CDrawContext::Invalidate()
			{
				Shader = nullptr;
				IndexBuffer = nullptr;
				InstanceBuffer = nullptr;
				TextureBindings.clear();

				ImmediateContext->OMSetBlendState(NULL, NULL, 0xffffffff);
				ImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			}

		} // D3D11
	} // Graphics
} // ion
