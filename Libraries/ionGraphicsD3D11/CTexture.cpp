
#include "CTexture.h"
#include "Utilities.h"


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			////////////
			// Params //
			////////////

			void CTexture::ApplyParams()
			{
				//static uint const FilterMatrix[2][2][2] =
				//{
				//	{ D3D11_FILTER_MIN_MAG_MIP_POINT, GL_LINEAR },
				//	{ GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST },
				//	{ GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR },
				//};

				static D3D11_FILTER const FilterLookup[2] =
				{
					D3D11_FILTER_MIN_MAG_MIP_POINT, D3D11_FILTER_MIN_MAG_MIP_LINEAR
				};

				static D3D11_TEXTURE_ADDRESS_MODE const WrapLookup[4] =
				{
					D3D11_TEXTURE_ADDRESS_CLAMP, D3D11_TEXTURE_ADDRESS_MIRROR, D3D11_TEXTURE_ADDRESS_WRAP, D3D11_TEXTURE_ADDRESS_BORDER
				};


				D3D11_SAMPLER_DESC SamplerDesc;
				SamplerDesc.Filter = Anisotropy > 0 ? D3D11_FILTER_ANISOTROPIC : FilterLookup[(int) MagFilter];
				SamplerDesc.MaxAnisotropy = Anisotropy;
				SamplerDesc.AddressU = SamplerDesc.AddressV = SamplerDesc.AddressW = WrapLookup[(int) WrapMode];
				SamplerDesc.MipLODBias = 0.f;
				SamplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
				SamplerDesc.BorderColor[0] = BorderColor.Red;
				SamplerDesc.BorderColor[1] = BorderColor.Green;
				SamplerDesc.BorderColor[2] = BorderColor.Blue;
				SamplerDesc.BorderColor[3] = BorderColor.Alpha;
				SamplerDesc.MinLOD = 0;
				SamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

				CheckedDXCall( Device->CreateSamplerState(& SamplerDesc, & SamplerState) );
			}

			CTexture::CTexture(ID3D11Device * Device, ID3D11DeviceContext * ImmediateContext)
			{
				this->Device = Device;
				this->ImmediateContext = ImmediateContext;
			}

			void CTexture::SetMinFilter(EFilter const MinFilter)
			{
				this->MinFilter = MinFilter;
				ApplyParams();
			}

			void CTexture::SetMagFilter(EFilter const MagFilter)
			{
				this->MagFilter = MagFilter;
				ApplyParams();
			}

			void CTexture::SetMipMapFilter(EFilter const MipMapFilter)
			{
				this->MipMapFilter = MipMapFilter;
				ApplyParams();
			}

			void CTexture::SetWrapMode(EWrapMode const WrapMode)
			{
				this->WrapMode = WrapMode;
				ApplyParams();
			}

			void CTexture::SetBorderColor(color4f const & BorderColor)
			{
				this->BorderColor = BorderColor;
				ApplyParams();
			}

			void CTexture::SetAnisotropy(float const Anisotropy)
			{
				this->Anisotropy = (int) Anisotropy;
				ApplyParams();
			}

			ITexture::EFilter CTexture::GetMinFilter()
			{
				return MinFilter;
			}

			ITexture::EFilter CTexture::GetMagFilter()
			{
				return MagFilter;
			}

			ITexture::EFilter CTexture::GetMipMapFilter()
			{
				return MipMapFilter;
			}

			ITexture::EWrapMode CTexture::GetWrapMode()
			{
				return WrapMode;
			}

			float CTexture::GetAnisotropy()
			{
				return (float) Anisotropy;
			}

			void CTexture::GenerateMipMaps()
			{
				if (MipMaps)
				{
					ImmediateContext->GenerateMips(ShaderResourceView);
				}
			}

			////////////
			// Lookup //
			////////////

			DXGI_FORMAT const CTexture::InternalFormatMatrix[4][12] =
			{

				// Components
				// -----
				// R = 0,
				// RG = 1,
				// RGB = 2,
				// RGBA = 3,

				// Type
				// ----
				// Fix8 = 0,
				// Fix16 = 1,
				// Float16 = 2,
				// Float32 = 3,
				// SignedInt8 = 4,
				// SignedInt16 = 5,
				// SignedInt24 = 6,
				// UnsignedInt8 = 7,
				// UnsignedInt16 = 8,
				// UnsignedInt24 = 9,
				// DepthStencil = 10,
				// Depth32 = 11

				{
					DXGI_FORMAT_R8_UNORM,
					DXGI_FORMAT_R16_UNORM,
					DXGI_FORMAT_R16_FLOAT,
					DXGI_FORMAT_R32_FLOAT,
					DXGI_FORMAT_R8_SINT,
					DXGI_FORMAT_R16_SINT,
					DXGI_FORMAT_R32_SINT,
					DXGI_FORMAT_R8_UINT,
					DXGI_FORMAT_R16_UINT,
					DXGI_FORMAT_R32_UINT,
					DXGI_FORMAT_R24G8_TYPELESS,
					DXGI_FORMAT_R32_TYPELESS,
				},
				{
					DXGI_FORMAT_R8G8_UNORM,
					DXGI_FORMAT_R16G16_UNORM,
					DXGI_FORMAT_R16G16_FLOAT,
					DXGI_FORMAT_R32G32_FLOAT,
					DXGI_FORMAT_R8G8_SINT,
					DXGI_FORMAT_R16G16_SINT,
					DXGI_FORMAT_R32G32_SINT,
					DXGI_FORMAT_R8G8_UINT,
					DXGI_FORMAT_R16G16_UINT,
					DXGI_FORMAT_R32G32_UINT,
					DXGI_FORMAT_R24G8_TYPELESS,
					DXGI_FORMAT_R32_TYPELESS,
				},
				{
					DXGI_FORMAT_UNKNOWN,
					DXGI_FORMAT_UNKNOWN,
					DXGI_FORMAT_UNKNOWN,
					DXGI_FORMAT_R32G32B32_FLOAT,
					DXGI_FORMAT_UNKNOWN,
					DXGI_FORMAT_UNKNOWN,
					DXGI_FORMAT_R32G32B32_SINT,
					DXGI_FORMAT_UNKNOWN,
					DXGI_FORMAT_UNKNOWN,
					DXGI_FORMAT_R32G32B32_UINT,
					DXGI_FORMAT_R24G8_TYPELESS,
					DXGI_FORMAT_R32_TYPELESS,
				},
				{
					DXGI_FORMAT_R8G8B8A8_UNORM,
					DXGI_FORMAT_R16G16B16A16_UNORM,
					DXGI_FORMAT_R16G16B16A16_FLOAT,
					DXGI_FORMAT_R32G32B32A32_FLOAT,
					DXGI_FORMAT_R8G8B8A8_SINT,
					DXGI_FORMAT_R16G16B16A16_SINT,
					DXGI_FORMAT_R32G32B32A32_SINT,
					DXGI_FORMAT_R8G8B8A8_UINT,
					DXGI_FORMAT_R16G16B16A16_UINT,
					DXGI_FORMAT_R32G32B32A32_UINT,
					DXGI_FORMAT_R24G8_TYPELESS,
					DXGI_FORMAT_R32_TYPELESS,
				}
			};


			///////////////
			// Texture2D //
			///////////////

			CTexture2D::CTexture2D(
				ID3D11Device * Device, ID3D11DeviceContext * ImmediateContext,
				vec2i const & Size, ITexture::EMipMaps const MipMapsMode,
				ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type)
				: CTexture(Device, ImmediateContext)
			{
				this->TextureSize = Size;

				MipMaps = (MipMapsMode == ITexture::EMipMaps::True);

				D3D11_TEXTURE2D_DESC TexDesc;
				TexDesc.Width = Size.X;
				TexDesc.Height = Size.Y;
				TexDesc.MipLevels = (MipMaps ? 0 : 1);
				TexDesc.ArraySize = 1;
				TexDesc.Format = InternalFormatMatrix[(int) Components][(int) Type];
				TexDesc.SampleDesc.Count = 1;
				TexDesc.SampleDesc.Quality = 0;
				TexDesc.Usage = D3D11_USAGE_DEFAULT;
				TexDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
				if (Type == EInternalFormatType::DepthStencil)// || Type == EInternalFormatType::Depth32)
				{
					if (Components != EFormatComponents::R)
					{
						Log::Warn("Cannot create a DepthStencil texture with more than a single channel");
					}
					TexDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_DEPTH_STENCIL;
				}
				TexDesc.CPUAccessFlags = 0;
				TexDesc.MiscFlags = (MipMaps ? D3D11_RESOURCE_MISC_GENERATE_MIPS : 0);

				if (TexDesc.Format == DXGI_FORMAT_UNKNOWN)
				{
					Log::Error("Attempting to create texture with unsupported RGB format - use RGBA");
					TexDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				}

				CheckedDXCall( Device->CreateTexture2D(& TexDesc, NULL, & Texture2D) );

				D3D11_SHADER_RESOURCE_VIEW_DESC ResourceDesc;
				ResourceDesc.Format = TexDesc.Format;

				if (Type == EInternalFormatType::DepthStencil)
				{
					ResourceDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
				}
				//if (Type == EInternalFormatType::Depth32)
				//{
				//	ResourceDesc.Format = DXGI_FORMAT_R32_FLOAT;
				//}

				ResourceDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
				ResourceDesc.Texture2D.MostDetailedMip = 0;
				ResourceDesc.Texture2D.MipLevels = -1;

				CheckedDXCall( Device->CreateShaderResourceView(Texture2D, & ResourceDesc, & ShaderResourceView) );

				ApplyParams();
			}

			void CTexture2D::Upload(void const * const Data, vec2i const & Size, EFormatComponents const Components, EScalarType const Type)
			{
				if (Size != TextureSize)
				{
					Log::Error("D3D11::Texture2D upload size does not match storage size.");
				}

				UploadSubRegion(Data, vec2i(0, 0), Size, Components, Type);
			}

			void CTexture2D::UploadSubRegion(void const * const Data, vec2i const & Offset, vec2i const & Size, EFormatComponents const Components, EScalarType const Type)
			{
				UINT const DataSize = ((UINT) Components + 1) * (UINT) GetScalarTypeSize(Type);
				UINT const RowPitch = DataSize * Size.X;
				UINT const DepthPitch = DataSize * Size.X * Size.Y;

				D3D11_BOX Box;
				Box.left = Offset.X;
				Box.right = Offset.X + Size.X;
				Box.top = Offset.Y;
				Box.bottom = Offset.Y + Size.Y;
				Box.front = 0;
				Box.back = 1;

				if (Texture2D)
				{
					ImmediateContext->UpdateSubresource(Texture2D, 0, & Box, Data, RowPitch, DepthPitch);
				}

				if (MipMaps)
				{
					ImmediateContext->GenerateMips(ShaderResourceView);
				}
			}

			void CTexture2D::GetData(void * const Data, vec2i const & Size, EFormatComponents const Components, EScalarType const Type)
			{
				D3D11_TEXTURE2D_DESC TextureDesc;
				Texture2D->GetDesc(& TextureDesc);

				TextureDesc.Usage = D3D11_USAGE_STAGING;
				TextureDesc.BindFlags = 0;
				TextureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
				TextureDesc.MiscFlags = 0;

				ID3D11Texture2D * StagingTexture = nullptr;
				CheckedDXCall( Device->CreateTexture2D(& TextureDesc, nullptr, & StagingTexture) );
				ImmediateContext->CopyResource(StagingTexture, Texture2D);

				D3D11_MAPPED_SUBRESOURCE ResourceDesc;
				CheckedDXCall( ImmediateContext->Map(StagingTexture, 0, D3D11_MAP_READ, 0, & ResourceDesc) );

				int const BytesPerPixel = ((int) Components + 1) * (int) GetScalarTypeSize(Type);
				for (int i = 0; i < Size.Y; ++ i)
				{
					std::memcpy(
						(byte *) Data               + Size.X * BytesPerPixel * i,
						(byte *) ResourceDesc.pData + ResourceDesc.RowPitch * i,
						Size.X * BytesPerPixel);
				}

				ImmediateContext->Unmap(StagingTexture, 0);
				StagingTexture->Release();
			}


			////////////////////
			// Texture2DArray //
			////////////////////

			void CTexture2DArray::Upload(void const * const Data, vec3i const & Size, EFormatComponents const Components, EScalarType const Type)
			{
				if (Size != TextureSize)
				{
					Log::Error("GL::Texture3D upload size does not match storage size.");
				}

				UploadSubRegion(Data, vec3i(0, 0, 0), Size, Components, Type);
			}

			void CTexture2DArray::UploadSubRegion(void const * const Data, vec3i const & Offset, vec3i const & Size, EFormatComponents const Components, EScalarType const Type)
			{
			}


			///////////////
			// Texture3D //
			///////////////

			void CTexture3D::Upload(void const * const Data, vec3i const & Size, EFormatComponents const Components, EScalarType const Type)
			{
				if (Size != TextureSize)
				{
					Log::Error("GL::Texture3D upload size does not match storage size.");
				}

				UploadSubRegion(Data, vec3i(0, 0, 0), Size, Components, Type);
			}

			void CTexture3D::UploadSubRegion(void const * const Data, vec3i const & Offset, vec3i const & Size, EFormatComponents const Components, EScalarType const Type)
			{
			}


			////////////////////
			// TextureCubeMap //
			////////////////////

			void CTextureCubeMap::Upload(EFace const Face, void const * const Data, vec2i const & Size, EFormatComponents const Components, EScalarType const Type)
			{
				if (Size != TextureSize)
				{
					Log::Error("GL::Texture3D upload size does not match storage size.");
				}

				UploadSubRegion(Face, Data, vec2i(0, 0), Size, Components, Type);
			}

			void CTextureCubeMap::UploadSubRegion(EFace const Face, void const * const Data, vec2i const & Offset, vec2i const & Size, EFormatComponents const Components, EScalarType const Type)
			{
			}

		}
	}
}
