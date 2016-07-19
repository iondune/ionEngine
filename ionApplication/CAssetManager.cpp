
#include "CAssetManager.h"


namespace ion
{

	void CAssetManager::Init(CGraphicsAPI * GraphicsAPI)
	{}

	SharedPointer<Graphics::IShaderProgram> CAssetManager::LoadShader(string const & Name)
	{
		if (! GraphicsAPI)
		{
			Log::Error("CAssetManager being used without being initialized, Shader '%s' will not be loaded.", Name);
			return nullptr;
		}

		for (string AssetPath : AssetPaths)
		{
			if (! File::Exists(AssetPath + ShaderPath + Name + ".vert"))
			{
				continue;
			}

			SharedPointer<Graphics::IVertexShader> VertexShader = GraphicsAPI->CreateVertexShaderFromFile(AssetPath + ShaderPath + Name + ".vert");
			SharedPointer<Graphics::IPixelShader> PixelShader = GraphicsAPI->CreatePixelShaderFromFile(AssetPath + ShaderPath + Name + ".frag");

			if (! VertexShader)
			{
				Log::Error("Failed to compile vertex shader '%s'", Name);
				return nullptr;
			}

			if (! PixelShader)
			{
				Log::Error("Failed to compile pixel shader '%s'", Name);
				return nullptr;
			}

			SharedPointer<Graphics::IShaderProgram> ShaderProgram = GraphicsAPI->CreateShaderProgram();
			ShaderProgram->SetVertexStage(VertexShader);
			ShaderProgram->SetPixelStage(PixelShader);

			return ShaderProgram;
		}

		Log::Error("Cannot find shader file in any asset directory: '%s'", Name);
		return nullptr;
	}

	SharedPointer<Graphics::ITexture2D> CAssetManager::LoadTexture(string const & FileName, Graphics::ITexture::EMipMaps const MipMaps)
	{
		if (! GraphicsAPI)
		{
			Log::Error("CAssetManager being used without being initialized, Texture '%s' will not be loaded.", FileName);
			return nullptr;
		}

		for (string AssetPath : AssetPaths)
		{
			if (! File::Exists(AssetPath + TexturePath + FileName))
			{
				continue;
			}

			CImage * Image = CImage::Load(AssetPath + TexturePath + FileName);
			if (Image)
			{
				return GraphicsAPI->CreateTexture2D(Image, MipMaps);
			}
			else
			{
				return nullptr;
			}
		}

		Log::Error("Cannot find image file in any asset directory: '%s'", FileName);
		return nullptr;
	}

	SharedPointer<Graphics::ITexture3D> CAssetManager::Load3DTexture(const std::vector<string> & FileNames, Graphics::ITexture::EMipMaps const MipMaps)
	{
		if (! GraphicsAPI)
		{
			Log::Error("CAssetManager being used without being initialized, Textures will not be loaded");
			return nullptr;
		}
		std::vector<CImage *> ImgArr;
		vec2u setSize(0,0);
		

		for(string FileName : FileNames)
		{
			for (string AssetPath : AssetPaths)
			{
				if (! File::Exists(AssetPath + TexturePath + FileName))
				{
					continue;
				}

				CImage * Image = CImage::Load(AssetPath + TexturePath + FileName);

				if (Image)
				{
					if(setSize[0] == 0)
					{
						setSize = Image->GetSize();
					}
					else
					{
						assert(Image->GetSize() == setSize);
					}
					ImgArr.push_back(Image);
				}
				else
				{
					return nullptr;
					Log::Error("Cannot find image file in any asset directory: '%s'", FileName);

				}
			}
		}
		Graphics::ITexture::EFormatComponents Format = Graphics::ITexture::EFormatComponents::R;

		switch (ImgArr[0]->GetChannels())
		{
		case 2:
			Format = Graphics::ITexture::EFormatComponents::RG;
			break;
		case 3:
			Format = Graphics::ITexture::EFormatComponents::RGB;
			break;
		case 4:
			Format = Graphics::ITexture::EFormatComponents::RGBA;
			break;
		}
		vec3u size3D(setSize[0], setSize[1], (uint) ImgArr.size());
		//Load and combine data
		
		SharedPointer<Graphics::ITexture3D> Texture3D = GraphicsAPI->CreateTexture3D(size3D,MipMaps,Format,Graphics::ITexture::EInternalFormatType::Fix8);
		for(int i = 0; i < ImgArr.size(); i++)
		{
			CImage * ImagePtr  = ImgArr[i];
			Texture3D->UploadSubRegion(
				ImagePtr->GetData(),
				vec3u(0,0,i),
				vec3u(setSize[0],setSize[1],1),
				Format,
				Graphics::EScalarType::UnsignedInt8);
		}
		return Texture3D;
	}

	SharedPointer<Graphics::ITextureCubeMap> CAssetManager::LoadCubeMapTexture(string const & FileNameLeft, string const & FileNameRight, string const & FileNameUp, string const & FileNameDown, string const & FileNameFront, string const & FileNameBack, Graphics::ITexture::EMipMaps const MipMaps)
	{
		if (! GraphicsAPI)
		{
			Log::Error("CAssetManager being used without being initialized, Texture '%s' etc. will not be loaded.", FileNameLeft);
			return nullptr;
		}

		vector<string> FileNames;
		FileNames.push_back(FileNameLeft);
		FileNames.push_back(FileNameRight);
		FileNames.push_back(FileNameUp);
		FileNames.push_back(FileNameDown);
		FileNames.push_back(FileNameFront);
		FileNames.push_back(FileNameBack);

		vector<CImage *> Images;
		Images.resize(6, nullptr);

		for (int i = 0; i < 6; ++ i)
		{
			for (string AssetPath : AssetPaths)
			{
				if (! File::Exists(AssetPath + TexturePath + FileNames[i]))
				{
					continue;
				}

				CImage * Image = CImage::Load(AssetPath + TexturePath + FileNames[i]);
				if (Image)
				{
					Image->FlipY();
					Images[i] = Image;
					break;
				}
				else
				{
					Log::Error("Failed to open image: '%s'", FileNames[i]);
					return nullptr;
				}
			}

			if (! Images[i])
			{
				Log::Error("Cannot find image file in any asset directory: '%s'", FileNames[i]);
				return nullptr;
			}
		}

		return GraphicsAPI->CreateTextureCubeMap(Images, MipMaps);
	}

	Scene::CSimpleMesh * CAssetManager::LoadMesh(string const & FileName)
	{
		if (! GraphicsAPI)
		{
			Log::Error("CAssetManager being used without being initialized, Texture '%s' will not be loaded.", FileName);
			return nullptr;
		}

		for (string AssetPath : AssetPaths)
		{
			if (! File::Exists(AssetPath + MeshPath + FileName))
			{
				continue;
			}

			vector<Scene::CSimpleMesh *> Shapes = Scene::CGeometryCreator::LoadOBJFile(AssetPath + MeshPath + FileName, AssetPath + MeshPath);

			if (Shapes.size() == 0)
			{
				Log::Error("Failed to load mesh: %s", FileName);
				return nullptr;
			}
			else if (Shapes.size() > 1)
			{
				Log::Error("Mesh contains %d shapes but only one was expected: %s", Shapes.size(), FileName);
			}

			return Shapes[0];
		}

		Log::Error("Cannot find mesh file in any asset directory: '%s'", FileName);
		return nullptr;
	}

	vector<Scene::CSimpleMesh *> CAssetManager::LoadMeshes(string const & FileName)
	{
		vector<Scene::CSimpleMesh *> Meshes;

		if (! GraphicsAPI)
		{
			Log::Error("CAssetManager being used without being initialized, Texture '%s' will not be loaded.", FileName);
			return Meshes;
		}

		for (string AssetPath : AssetPaths)
		{
			if (! File::Exists(AssetPath + MeshPath + FileName))
			{
				continue;
			}

			Meshes = Scene::CGeometryCreator::LoadOBJFile(AssetPath + MeshPath + FileName, AssetPath + MeshPath);

			if (Meshes.size() == 0)
			{
				Log::Error("Failed to load mesh: %s", FileName);
				return Meshes;
			}

			return Meshes;
		}

		Log::Error("Cannot find mesh file in any asset directory: '%s'", FileName);
		return Meshes;
	}

	void CAssetManager::AddAssetPath(string const & Path)
	{
		AssetPaths.push_back(Path + "/");
	}

	void CAssetManager::SetTexturePath(string const & Path)
	{
		TexturePath = Path + "/";
	}

	void CAssetManager::SetShaderPath(string const & Path)
	{
		ShaderPath = Path + "/";
	}

	void CAssetManager::SetMeshPath(string const & Path)
	{
		MeshPath = Path + "/";
	}

}
