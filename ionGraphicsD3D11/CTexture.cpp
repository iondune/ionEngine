
#include "CTexture.h"
#include "Utilities.h"
#include <glad/glad.h>


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{

			////////////
			// Params //
			////////////

			void CTexture::ApplyParams()
			{
				static uint const FilterMatrix[3][2] =
				{
					{GL_NEAREST, GL_LINEAR},
					{GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST},
					{GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR},
				};

				static uint const FilterLookup[2] =
				{
					GL_NEAREST, GL_LINEAR
				};

				static uint const WrapLookup[4] =
				{
					GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT, GL_REPEAT, GL_CLAMP_TO_BORDER
				};

				int MipMapMode;
				if (MipMaps)
				{
					MipMapMode = 1 + (int) MipMapFilter;
				}
				else
				{
					MipMapMode = 0;
				}

				//(glTexParameteri(GetGLBindTextureTarget(), GL_TEXTURE_MIN_FILTER, FilterMatrix[MipMapMode][(int) MinFilter]));
				//(glTexParameteri(GetGLBindTextureTarget(), GL_TEXTURE_MAG_FILTER, FilterLookup[(int) MagFilter]));

				//(glTexParameteri(GetGLBindTextureTarget(), GL_TEXTURE_WRAP_S, WrapLookup[(int) WrapMode]));
				//(glTexParameteri(GetGLBindTextureTarget(), GL_TEXTURE_WRAP_T, WrapLookup[(int) WrapMode]));
				//(glTexParameteri(GetGLBindTextureTarget(), GL_TEXTURE_WRAP_R, WrapLookup[(int) WrapMode]));
				float BorderColorValues[4] = 
				{
					BorderColor.Red,
					BorderColor.Green,
					BorderColor.Blue,
					BorderColor.Alpha,
				};
				//(glTexParameterfv(GetGLBindTextureTarget(), GL_TEXTURE_BORDER_COLOR, BorderColorValues));

				float LargestAnisotropy = 2.f;
				//(glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, & LargestAnisotropy));
				if (Anisotropy < 0.f)
					Anisotropy = LargestAnisotropy;
				//(glTexParameterf(GetGLBindTextureTarget(), GL_TEXTURE_MAX_ANISOTROPY_EXT, Clamp(Anisotropy, 0.f, LargestAnisotropy)));
			}

			void CTexture::SetMinFilter(EFilter const MinFilter)
			{
				if (IsInteger && MinFilter != EFilter::Nearest)
				{
					// See https://www.khronos.org/registry/OpenGL/extensions/EXT/EXT_texture_integer.txt
					Log::Error("Cannot use filter mode other than Nearest on an Integer texture");
				}
				else
				{
					this->MinFilter = MinFilter;
					ApplyParams();
				}
			}

			void CTexture::SetMagFilter(EFilter const MagFilter)
			{
				if (IsInteger && MagFilter != EFilter::Nearest)
				{
					// See https://www.khronos.org/registry/OpenGL/extensions/EXT/EXT_texture_integer.txt
					Log::Error("Cannot use filter mode other than Nearest on an Integer texture");
				}
				else
				{
					this->MagFilter = MagFilter;
					ApplyParams();
				}
			}

			void CTexture::SetMipMapFilter(EFilter const MipMapFilter)
			{
				if (IsInteger && MipMapFilter != EFilter::Nearest)
				{
					// See https://www.khronos.org/registry/OpenGL/extensions/EXT/EXT_texture_integer.txt
					Log::Error("Cannot use filter mode other than Nearest on an Integer texture");
				}
				else
				{
					this->MipMapFilter = MipMapFilter;
					ApplyParams();
				}
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
				this->Anisotropy = Anisotropy;
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
				return Anisotropy;
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

			uint const CTexture::InternalFormatMatrix[4][11] =
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

				{ GL_R8,    GL_R16,    GL_R16F,    GL_R32F,    GL_R8I,    GL_R16I,    GL_R32I,    GL_R8UI,    GL_R16UI,    GL_R32UI,    GL_DEPTH_COMPONENT32 },
				{ GL_RG8,   GL_RG16,   GL_RG16F,   GL_RG32F,   GL_RG8I,   GL_RG16I,   GL_RG32I,   GL_RG8UI,   GL_RG16UI,   GL_RG32UI,   GL_DEPTH_COMPONENT32 },
				{ GL_RGB8,  GL_RGB16,  GL_RGB16F,  GL_RGB32F,  GL_RGB8I,  GL_RGB16I,  GL_RGB32I,  GL_RGB8UI,  GL_RGB16UI,  GL_RGB32UI,  GL_DEPTH_COMPONENT32 },
				{ GL_RGBA8, GL_RGBA16, GL_RGBA16F, GL_RGBA32F, GL_RGBA8I, GL_RGBA16I, GL_RGBA32I, GL_RGBA8UI, GL_RGBA16UI, GL_RGBA32UI, GL_DEPTH_COMPONENT32 },
			};

			uint const CTexture::FormatMatrix[4][2] =
			{
				GL_RED,  GL_RED_INTEGER,
				GL_RG,   GL_RG_INTEGER,
				GL_RGB,  GL_RGB_INTEGER,
				GL_RGBA, GL_RGBA_INTEGER,
			};


			string const CTexture::InternalFormatStringMatrix[4][10] =
			{
				{ "GL_R8", "GL_R16F", "GL_R32F", "GL_R8I", "GL_R16I", "GL_R32I", "GL_R8UI", "GL_R16UI", "GL_R32UI", "GL_DEPTH_COMPONENT32" },
				{ "GL_RG8", "GL_RG16F", "GL_RG32F", "GL_RG8I", "GL_RG16I", "GL_RG32I", "GL_RG8UI", "GL_RG16UI", "GL_RG32UI", "GL_DEPTH_COMPONENT32" },
				{ "GL_RGB8", "GL_RGB16F", "GL_RGB32F", "GL_RGB8I", "GL_RGB16I", "GL_RGB32I", "GL_RGB8UI", "GL_RGB16UI", "GL_RGB32UI", "GL_DEPTH_COMPONENT32" },
				{ "GL_RGBA8", "GL_RGBA16F", "GL_RGBA32F", "GL_RGBA8I", "GL_RGBA16I", "GL_RGBA32I", "GL_RGBA8UI", "GL_RGBA16UI", "GL_RGBA32UI", "GL_DEPTH_COMPONENT32" },
			};

			string const CTexture::FormatStringMatrix[4] =
			{
				"GL_RED",
				"GL_RG",
				"GL_RGB",
				"GL_RGBA"
			};


			///////////////
			// Texture2D //
			///////////////

			void CTexture2D::Upload(void const * const Data, vec2i const & Size, EFormatComponents const Components, EScalarType const Type)
			{
				if (Size != TextureSize)
				{
					Log::Error("GL::Texture2D upload size does not match storage size.");
					Log::Error("Handle is %u", Handle);
				}

				UploadSubRegion(Data, vec2i(0, 0), Size, Components, Type);
			}

			void CTexture2D::UploadSubRegion(void const * const Data, vec2i const & Offset, vec2i const & Size, EFormatComponents const Components, EScalarType const Type)
			{
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
					Log::Error("Handle is %u", Handle);
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
					Log::Error("Handle is %u", Handle);
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
					Log::Error("Handle is %u", Handle);
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
