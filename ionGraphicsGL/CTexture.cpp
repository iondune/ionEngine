
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

				static uint const WrapLookup[3] =
				{
					GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT, GL_REPEAT
				};

				int MipMapMode;
				if (MipMaps)
					MipMapMode = 1 + (int) MipMapFilter;
				else
					MipMapMode = 0;

				int PreviouslyBoundTexture;
				CheckedGLCall(glGetIntegerv(GetGLTextureBindingEnum(), & PreviouslyBoundTexture));
				CheckedGLCall(glBindTexture(GetGLBindTextureTarget(), Handle));
				CheckedGLCall(glTexParameteri(GetGLBindTextureTarget(), GL_TEXTURE_MIN_FILTER, FilterMatrix[MipMapMode][(int) MinFilter]));
				CheckedGLCall(glTexParameteri(GetGLBindTextureTarget(), GL_TEXTURE_MAG_FILTER, FilterLookup[(int) MagFilter]));

				CheckedGLCall(glTexParameteri(GetGLBindTextureTarget(), GL_TEXTURE_WRAP_S, WrapLookup[(int) WrapMode]));
				CheckedGLCall(glTexParameteri(GetGLBindTextureTarget(), GL_TEXTURE_WRAP_T, WrapLookup[(int) WrapMode]));
				CheckedGLCall(glTexParameteri(GetGLBindTextureTarget(), GL_TEXTURE_WRAP_R, WrapLookup[(int) WrapMode]));

				float LargestAnisotropy = 2.f;
				CheckedGLCall(glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, & LargestAnisotropy));
				if (Anisotropy < 0.f)
					Anisotropy = LargestAnisotropy;
				CheckedGLCall(glTexParameterf(GetGLBindTextureTarget(), GL_TEXTURE_MAX_ANISOTROPY_EXT, Clamp(Anisotropy, 0.f, LargestAnisotropy)));
				CheckedGLCall(glBindTexture(GetGLBindTextureTarget(), PreviouslyBoundTexture));
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

			////////////
			// Lookup //
			////////////

			uint const CTexture::InternalFormatMatrix[4][10] =
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
				// Float16 = 1,
				// Float32 = 2,
				// SignedInt8 = 3,
				// SignedInt16 = 4,
				// SignedInt24 = 5,
				// UnsignedInt8 = 6,
				// UnsignedInt16 = 7,
				// UnsignedInt24 = 8,
				// Depth = 9,

				{ GL_R8,    GL_R16F,    GL_R32F,    GL_R8I,    GL_R16I,    GL_R32I,    GL_R8UI,    GL_R16UI,    GL_R32UI,    GL_DEPTH_COMPONENT32 },
				{ GL_RG8,   GL_RG16F,   GL_RG32F,   GL_RG8I,   GL_RG16I,   GL_RG32I,   GL_RG8UI,   GL_RG16UI,   GL_RG32UI,   GL_DEPTH_COMPONENT32 },
				{ GL_RGB8,  GL_RGB16F,  GL_RGB32F,  GL_RGB8I,  GL_RGB16I,  GL_RGB32I,  GL_RGB8UI,  GL_RGB16UI,  GL_RGB32UI,  GL_DEPTH_COMPONENT32 },
				{ GL_RGBA8, GL_RGBA16F, GL_RGBA32F, GL_RGBA8I, GL_RGBA16I, GL_RGBA32I, GL_RGBA8UI, GL_RGBA16UI, GL_RGBA32UI, GL_DEPTH_COMPONENT32 },
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
				CheckedGLCall(glBindTexture(GL_TEXTURE_2D, Handle));
				CheckExistingErrors(CTexture2D::SubImage);
				glTexSubImage2D(GL_TEXTURE_2D, 0, Offset.X, Offset.Y, Size.X, Size.Y, FormatMatrix[(int) Components][IsInteger ? 1 : 0], Util::ScalarTypeMatrix[(int) Type], Data);
				if (OpenGLError())
				{
					Log::Error("Error occured during glTexSubImage2D: %s", GetOpenGLError());
					Log::Error("Handle is %u", Handle);
					Log::Error("Offset is %s", Offset);
					Log::Error("Size is %s", Size);
					Log::Error("Format is %s", FormatStringMatrix[(int) Components]);
					Log::Error("Type is %s", Util::ScalarTypeStringMatrix[(int) Type]);
				}
				else
				{
					if (MipMaps)
						CheckedGLCall(glGenerateMipmap(GL_TEXTURE_2D));
					ApplyParams();
				}
				CheckedGLCall(glBindTexture(GL_TEXTURE_2D, 0));
			}

			void CTexture2D::GetData(void * const Data, vec2i const & Size, EFormatComponents const Components, EScalarType const Type)
			{
				CheckedGLCall(glBindTexture(GL_TEXTURE_2D, Handle));
				CheckExistingErrors(CTexture2D::GetData);
				glGetTexImage(GL_TEXTURE_2D, 0, FormatMatrix[(int) Components][IsInteger ? 1 : 0], Util::ScalarTypeMatrix[(int) Type], Data);
				if (OpenGLError())
				{
					Log::Error("Error occured during glGetTexImage: %s", GetOpenGLError());
					Log::Error("Handle is %u", Handle);
					Log::Error("Size is %s", Size);
					Log::Error("Format is %s", FormatStringMatrix[(int) Components]);
					Log::Error("Type is %s", Util::ScalarTypeStringMatrix[(int) Type]);
				}
				else
				{
					if (MipMaps)
						CheckedGLCall(glGenerateMipmap(GL_TEXTURE_2D));
					ApplyParams();
				}
				CheckedGLCall(glBindTexture(GL_TEXTURE_2D, 0));
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
				CheckedGLCall(glBindTexture(GL_TEXTURE_2D_ARRAY, Handle));
				CheckExistingErrors(CTexture2DArray::SubImage);
				glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, Offset.X, Offset.Y, Offset.Z, Size.X, Size.Y, Size.Z, FormatMatrix[(int) Components][IsInteger ? 1 : 0], Util::ScalarTypeMatrix[(int) Type], Data);
				if (OpenGLError())
				{
					Log::Error("Error occured during glTexSubImage3D: %s", GetOpenGLError());
					Log::Error("Handle is %u", Handle);
					Log::Error("Offset is %s", Offset);
					Log::Error("Size is %s", Size);
					Log::Error("Format is %s", FormatStringMatrix[(int) Components]);
					Log::Error("Type is %s", Util::ScalarTypeStringMatrix[(int) Type]);
				}
				else
				{
					if (MipMaps)
						CheckedGLCall(glGenerateMipmap(GL_TEXTURE_2D_ARRAY));
					ApplyParams();
				}
				CheckedGLCall(glBindTexture(GL_TEXTURE_2D_ARRAY, 0));
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
				CheckedGLCall(glBindTexture(GL_TEXTURE_3D, Handle));
				CheckExistingErrors(CTexture3D::SubImage);
				glTexSubImage3D(GL_TEXTURE_3D, 0, Offset.X, Offset.Y, Offset.Z, Size.X, Size.Y, Size.Z, FormatMatrix[(int) Components][IsInteger ? 1 : 0], Util::ScalarTypeMatrix[(int) Type], Data);
				if (OpenGLError())
				{
					Log::Error("Error occured during glTexSubImage3D: %s", GetOpenGLError());
					Log::Error("Handle is %u", Handle);
					Log::Error("Offset is %s", Offset);
					Log::Error("Size is %s", Size);
					Log::Error("Format is %s", FormatStringMatrix[(int) Components]);
					Log::Error("Type is %s", Util::ScalarTypeStringMatrix[(int) Type]);
				}
				else
				{
					if (MipMaps)
						CheckedGLCall(glGenerateMipmap(GL_TEXTURE_3D));
					ApplyParams();
				}
				CheckedGLCall(glBindTexture(GL_TEXTURE_3D, 0));
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
				CheckedGLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, Handle));
				CheckExistingErrors(Texture2D::SubImage);
				glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + (int) Face, 0, Offset.X, Offset.Y, Size.X, Size.Y, FormatMatrix[(int) Components][IsInteger ? 1 : 0], Util::ScalarTypeMatrix[(int) Type], Data);
				if (OpenGLError())
				{
					Log::Error("Error occured during glTexSubImage2D for CTextureCubeMap: %s", GetOpenGLError());
					Log::Error("Handle is %u", Handle);
					Log::Error("Offset is %s", Offset);
					Log::Error("Size is %s", Size);
					Log::Error("Format is %s", FormatStringMatrix[(int) Components]);
					Log::Error("Type is %s", Util::ScalarTypeStringMatrix[(int) Type]);
				}
				else
				{
					if (MipMaps)
						CheckedGLCall(glGenerateMipmap(GL_TEXTURE_CUBE_MAP));
					ApplyParams();
				}
				CheckedGLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
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
