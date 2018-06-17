
#include "CTexture.h"
#include "Utilities.h"
#include <glad/glad.h>


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

			CTexture::CTexture(ID3D11Device * Device)
			{
				this->Device = Device;
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
					//(glBindTexture(GetGLBindTextureTarget(), Handle));
					//(glGenerateMipmap(GetGLBindTextureTarget()));
				}
			}

			////////////
			// Lookup //
			////////////

			DXGI_FORMAT const CTexture::InternalFormatMatrix[4][11] =
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
				// Depth = 10,

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
					DXGI_FORMAT_D32_FLOAT
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
					DXGI_FORMAT_D32_FLOAT
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
					DXGI_FORMAT_D32_FLOAT
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
					DXGI_FORMAT_D32_FLOAT
				}
			};


			///////////////
			// Texture2D //
			///////////////

			CTexture2D::CTexture2D(
				ID3D11Device * Device, ID3D11DeviceContext * ImmediateContext,
				vec2i const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type)
				: CTexture(Device)
			{
				this->ImmediateContext = ImmediateContext;
				this->TextureSize = Size;

				D3D11_TEXTURE2D_DESC TexDesc;
				TexDesc.Width = Size.X;
				TexDesc.Height = Size.Y;
				TexDesc.MipLevels = (MipMaps == ITexture::EMipMaps::True ? 0 : 1);
				TexDesc.ArraySize = 1;
				TexDesc.Format = InternalFormatMatrix[(int) Components][(int) Type];
				TexDesc.SampleDesc.Count = 1;
				TexDesc.SampleDesc.Quality = 0;
				TexDesc.Usage = D3D11_USAGE_DEFAULT;
				TexDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
				TexDesc.CPUAccessFlags = 0;
				TexDesc.MiscFlags = 0;

				Device->CreateTexture2D(& TexDesc, NULL, & Texture2D);

				D3D11_SHADER_RESOURCE_VIEW_DESC ResourceDesc;
				ResourceDesc.Format = TexDesc.Format;
				ResourceDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
				ResourceDesc.Texture2D.MostDetailedMip = 0;
				ResourceDesc.Texture2D.MipLevels = -1;

				Device->CreateShaderResourceView(Texture2D, & ResourceDesc, & ShaderResourceView);

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
				UINT const DataSize = ((int) Components + 1);
				UINT const RowPitch = DataSize * Size.X;
				UINT const DepthPitch = DataSize * Size.X * Size.Y;

				D3D11_BOX Box;
				Box.left = 0;
				Box.right = Size.X;
				Box.top = 0;
				Box.bottom = Size.Y;
				Box.front = 0;
				Box.back = 1;

				ImmediateContext->UpdateSubresource(Texture2D, 0, & Box, Data, RowPitch, DepthPitch);
			}

			void CTexture2D::GetData(void * const Data, vec2i const & Size, EFormatComponents const Components, EScalarType const Type)
			{
			}

			uint CTexture2D::GetGLBindTextureTarget() const
			{
				return GL_TEXTURE_2D;
			}

			uint CTexture2D::GetGLTextureBindingEnum() const
			{
				return GL_TEXTURE_BINDING_2D;
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

			uint CTexture2DArray::GetGLBindTextureTarget() const
			{
				return GL_TEXTURE_2D_ARRAY;
			}

			uint CTexture2DArray::GetGLTextureBindingEnum() const
			{
				return GL_TEXTURE_BINDING_2D_ARRAY;
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

			uint CTexture3D::GetGLBindTextureTarget() const
			{
				return GL_TEXTURE_3D;
			}

			uint CTexture3D::GetGLTextureBindingEnum() const
			{
				return GL_TEXTURE_BINDING_3D;
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

			uint CTextureCubeMap::GetGLBindTextureTarget() const
			{
				return GL_TEXTURE_CUBE_MAP;
			}

			uint CTextureCubeMap::GetGLTextureBindingEnum() const
			{
				return GL_TEXTURE_BINDING_CUBE_MAP;
			}
		}
	}
}
