
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
				static u32 const FilterMatrix[3][2] =
				{
					{GL_NEAREST, GL_LINEAR},
					{GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST},
					{GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR},
				};

				static u32 const FilterLookup[2] =
				{
					GL_NEAREST, GL_LINEAR
				};

				static u32 const WrapLookup[3] =
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

			void CTexture::SetAnisotropy(f32 const Anisotropy)
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

			f32 CTexture::GetAnisotropy()
			{
				return Anisotropy;
			}

			////////////
			// Lookup //
			////////////

			u32 const CTexture::InternalFormatMatrix[4][4] =
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
				// Depth = 3,

				{GL_R8, GL_R16F, GL_R32F, GL_DEPTH_COMPONENT24 },
				{GL_RG8, GL_RG16F, GL_RG32F, GL_DEPTH_COMPONENT24 },
				{GL_RGB8, GL_RGB16F, GL_RGB32F, GL_DEPTH_COMPONENT24 },
				{GL_RGBA8, GL_RGBA16F, GL_RGBA32F, GL_DEPTH_COMPONENT24 },
			};

			u32 const CTexture::FormatMatrix[4] =
			{
				GL_RED,
				GL_RG,
				GL_RGB,
				GL_RGBA
			};


			string const CTexture::InternalFormatStringMatrix[4][4] =
			{
				{ "GL_R8", "GL_R16F", "GL_R32F", "GL_DEPTH_COMPONENT24" },
				{ "GL_RG8", "GL_RG16F", "GL_RG32F", "GL_DEPTH_COMPONENT24" },
				{ "GL_RGB8", "GL_RGB16F", "GL_RGB32F", "GL_DEPTH_COMPONENT24" },
				{ "GL_RGBA8", "GL_RGBA16F", "GL_RGBA32F", "GL_DEPTH_COMPONENT24" },
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
	#if 0
			Texture2D::Texture2D(vec2u const & Size, bool const MipMaps, EFormatComponents const Components, EInternalFormatType const Type)
			{
			}
	#endif
			void CTexture2D::Upload(void const * const Data, vec2u const & Size, EFormatComponents const Components, EScalarType const Type)
			{
				if (Size != TextureSize)
				{
					cerr << "GL::Texture2D upload size does not match storage size." << endl;
					cerr << "Handle is " << Handle << endl;
				}

				UploadSubRegion(Data, vec2u(0, 0), Size, Components, Type);
			}

			void CTexture2D::UploadSubRegion(void const * const Data, vec2u const & Offset, vec2u const & Size, EFormatComponents const Components, EScalarType const Type)
			{
				CheckedGLCall(glBindTexture(GL_TEXTURE_2D, Handle));
				CheckExistingErrors(Texture2D::SubImage);
				glTexSubImage2D(GL_TEXTURE_2D, 0, Offset.X, Offset.Y, Size.X, Size.Y, FormatMatrix[(int) Components], Util::ScalarTypeMatrix[(int) Type], Data);
				if (OpenGLError())
				{
					cerr << "Error occured during glTexSubImage2D: " << GetOpenGLError() << endl;
					cerr << "Handle is " << Handle << endl;
					cerr << "Offset is " << Offset << endl;
					cerr << "Size is " << Size << endl;
					cerr << "Format is " << FormatStringMatrix[(int) Components] << endl;
					cerr << "Type is " << Util::ScalarTypeStringMatrix[(int) Type] << endl;
					cerr << endl;
				}
				else
				{
					if (MipMaps)
						CheckedGLCall(glGenerateMipmap(GL_TEXTURE_2D));
					ApplyParams();
				}
				CheckedGLCall(glBindTexture(GL_TEXTURE_2D, 0));
			}

			u32 CTexture2D::GetGLBindTextureTarget() const
			{
				return GL_TEXTURE_2D;
			}

			u32 CTexture2D::GetGLTextureBindingEnum() const
			{
				return GL_TEXTURE_BINDING_2D;
			}


			///////////////
			// Texture3D //
			///////////////
	#if 0
			Texture3D::Texture3D(vec3u const & Size, bool const MipMaps, EFormatComponents const Components, EInternalFormatType const Type)
			{
			}
	#endif
			void CTexture3D::Upload(void const * const Data, vec3u const & Size, EFormatComponents const Components, EScalarType const Type)
			{
				if (Size != TextureSize)
				{
					cerr << "GL::Texture3D upload size does not match storage size." << endl;
					cerr << "Handle is " << Handle << endl;
				}

				UploadSubRegion(Data, vec3u(0, 0, 0), Size, Components, Type);
			}

			void CTexture3D::UploadSubRegion(void const * const Data, vec3u const & Offset, vec3u const & Size, EFormatComponents const Components, EScalarType const Type)
			{
				CheckedGLCall(glBindTexture(GL_TEXTURE_3D, Handle));
				CheckExistingErrors(Texture2D::SubImage);
				glTexSubImage3D(GL_TEXTURE_3D, 0, Offset.X, Offset.Y, Offset.Z, Size.X, Size.Y, Size.Z, FormatMatrix[(int) Components], Util::ScalarTypeMatrix[(int) Type], Data);
				if (OpenGLError())
				{
					cerr << "Error occured during glTexSubImage3D: " << GetOpenGLError() << endl;
					cerr << "Handle is " << Handle << endl;
					cerr << "Offset is " << Offset << endl;
					cerr << "Size is " << Size << endl;
					cerr << "Format is " << FormatStringMatrix[(int) Components] << endl;
					cerr << "Type is " << Util::ScalarTypeStringMatrix[(int) Type] << endl;
					cerr << endl;
				}
				else
				{
					if (MipMaps)
						CheckedGLCall(glGenerateMipmap(GL_TEXTURE_3D));
					ApplyParams();
				}
				CheckedGLCall(glBindTexture(GL_TEXTURE_3D, 0));
			}

			u32 CTexture3D::GetGLBindTextureTarget() const
			{
				return GL_TEXTURE_3D;
			}

			u32 CTexture3D::GetGLTextureBindingEnum() const
			{
				return GL_TEXTURE_BINDING_3D;
			}

			void CTextureCubeMap::Upload(EFace const Face, void const * const Data, vec2u const & Size, EFormatComponents const Components, EScalarType const Type)
			{
				if (Size != TextureSize)
				{
					cerr << "GL::Texture3D upload size does not match storage size." << endl;
					cerr << "Handle is " << Handle << endl;
				}

				UploadSubRegion(Face, Data, vec2u(0, 0), Size, Components, Type);
			}

			void CTextureCubeMap::UploadSubRegion(EFace const Face, void const * const Data, vec2u const & Offset, vec2u const & Size, EFormatComponents const Components, EScalarType const Type)
			{
				CheckedGLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, Handle));
				CheckExistingErrors(Texture2D::SubImage);
				glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + (int) Face, 0, Offset.X, Offset.Y, Size.X, Size.Y, FormatMatrix[(int) Components], Util::ScalarTypeMatrix[(int) Type], Data);
				if (OpenGLError())
				{
					cerr << "Error occured during glTexSubImage2D for CTextureCubeMap: " << GetOpenGLError() << endl;
					cerr << "Handle is " << Handle << endl;
					cerr << "Offset is " << Offset << endl;
					cerr << "Size is " << Size << endl;
					cerr << "Format is " << FormatStringMatrix[(int) Components] << endl;
					cerr << "Type is " << Util::ScalarTypeStringMatrix[(int) Type] << endl;
					cerr << endl;
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
