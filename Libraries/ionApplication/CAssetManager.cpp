
#include "CAssetManager.h"

#include <ionGUI.h>


namespace ion
{

	void CAssetManager::Init(CGraphicsAPI * GraphicsAPI)
	{}

	SharedPointer<Graphics::IShader> CAssetManager::LoadShader(string const & Name, int const Stages)
	{
		if (! GraphicsAPI)
		{
			Log::Error("CAssetManager being used without being initialized, Shader '%s' will not be loaded.", Name);
			return nullptr;
		}

		ShaderInfos.push_back(SShaderInfo());
		SShaderInfo & info = ShaderInfos.back();
		info.Name     = Name;
		info.Stages   = Stages;
		info.Compiled = false;

		string const FileName =  Name + ".hlsl";

		vector<string> ShaderPaths;
		for (string const & AssetPath : AssetPaths)
		{
			ShaderPaths.push_back(AssetPath + ShaderPath);
		}

		for (string const & Path : ShaderPaths)
		{
			string const FilePath = Path + FileName;

			if (! File::Exists(FilePath))
			{
				// Check other asset paths
				continue;
			}

			info.FoundIn = Path;

			SharedPointer<Graphics::IVertexStage> VertexShader;
			SharedPointer<Graphics::IGeometryStage> GeometryShader;
			SharedPointer<Graphics::IPixelStage> PixelShader;

			if (Stages & Graphics::EShaderType::Vertex)
			{
				VertexShader = GraphicsAPI->CreateVertexStageFromFile(FilePath, ShaderPaths, & info.ErrorsAndWarnings);
				if (! VertexShader)
				{
					Log::Error("Failed to compile vertex shader '%s': '%s'", Name, FilePath);
					return nullptr;
				}
			}

			if (Stages & Graphics::EShaderType::Geometry)
			{
				GeometryShader = GraphicsAPI->CreateGeometryStageFromFile(FilePath, ShaderPaths, & info.ErrorsAndWarnings);

				if (! GeometryShader)
				{
					Log::Error("Failed to compile geometry shader '%s': '%s'", Name, FilePath);
					return nullptr;
				}
			}

			if (Stages & Graphics::EShaderType::Pixel)
			{
				PixelShader = GraphicsAPI->CreatePixelStageFromFile(FilePath, ShaderPaths, & info.ErrorsAndWarnings);
				if (! PixelShader)
				{
					Log::Error("Failed to compile pixel shader '%s': '%s'", Name, FilePath);
					return nullptr;
				}
			}


			SharedPointer<Graphics::IShader> Shader = GraphicsAPI->CreateShaderProgram();

			if (VertexShader)
			{
				Shader->SetVertexStage(VertexShader);
			}
			if (GeometryShader)
			{
				Shader->SetGeometryStage(GeometryShader);
			}
			if (PixelShader)
			{
				Shader->SetPixelStage(PixelShader);
			}

			Shader->Link();

			info.Compiled = true;
			info.ShaderHandle = Shader;

			return Shader;
		}

		Log::Error("Cannot find shader file in any asset directory: '%s'", Name);
		return nullptr;
	}

	CImage * CAssetManager::LoadImage(string const & FileName)
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

			return CImage::Load(AssetPath + TexturePath + FileName);
		}

		Log::Error("Cannot find image file in any asset directory: '%s'", FileName);
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
		vec2i setSize(0, 0);


		for (string FileName : FileNames)
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
					if (setSize[0] == 0)
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
		Graphics::ITexture::EFormatComponents const Format = Graphics::ITexture::EFormatComponents::RGBA;

		vec3i size3D(setSize[0], setSize[1], (uint) ImgArr.size());
		//Load and combine data

		SharedPointer<Graphics::ITexture3D> Texture3D = GraphicsAPI->CreateTexture3D(size3D, MipMaps, Format, Graphics::ITexture::EInternalFormatType::Fix8);
		for (int i = 0; i < ImgArr.size(); i++)
		{
			CImage * ImagePtr = ImgArr[i];
			Texture3D->UploadSubRegion(
				ImagePtr->GetData(),
				vec3i(0, 0, i),
				vec3i(setSize[0], setSize[1], 1),
				Format,
				Graphics::EScalarType::UnsignedInt8);
		}
		return Texture3D;
	}

	SharedPointer<Graphics::ITexture2DArray> CAssetManager::Load2DTextureArray(const std::vector<string> & FileNames, Graphics::ITexture::EMipMaps const MipMaps)
	{
		if (! GraphicsAPI)
		{
			Log::Error("CAssetManager being used without being initialized, Textures will not be loaded");
			return nullptr;
		}
		std::vector<CImage *> ImgArr;
		vec2i setSize(0, 0);


		for (string FileName : FileNames)
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
					if (setSize[0] == 0)
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
		Graphics::ITexture::EFormatComponents const Format = Graphics::ITexture::EFormatComponents::RGBA;

		vec3i size3D(setSize[0], setSize[1], (uint) ImgArr.size());
		//Load and combine data

		SharedPointer<Graphics::ITexture2DArray> Texture3D = GraphicsAPI->CreateTexture2DArray(size3D, MipMaps, Format, Graphics::ITexture::EInternalFormatType::Fix8);
		for (int i = 0; i < ImgArr.size(); i++)
		{
			CImage * ImagePtr = ImgArr[i];
			Texture3D->UploadSubRegion(
				ImagePtr->GetData(),
				vec3i(0, 0, i),
				vec3i(setSize[0], setSize[1], 1),
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

	Scene::CSimpleMesh * CAssetManager::LoadMeshMerged(string const & FileName)
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
				for (int i = 1; i < Shapes.size(); ++ i)
				{
					Shapes[0] = Scene::CGeometryCreator::Intersect(Shapes[0], Shapes[i]);
				}
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

	string CAssetManager::GetName()
	{
		return "Asset Manager"s;
	}

	void CAssetManager::DrawGUIControls()
	{
		ImGui::Text("TexturePath: '%s'", TexturePath.c_str());
		ImGui::Text("ShaderPath: '%s'",  ShaderPath.c_str());
		ImGui::Text("MeshPath: '%s'",    MeshPath.c_str());
		ImGui::Text("AssetPaths (%d)",   static_cast<int>(AssetPaths.size()));

		int i = 0;
		for (string path : AssetPaths)
		{
			ImGui::Text("  AssetPath[%d] = '%s'", i , path.c_str());
			i ++;
		}

		ImGui::Separator();

		i = 0;
		for (SShaderInfo const & info : ShaderInfos)
		{
			ImGui::Text("Shader[%d] = '%s'", i, info.Name.c_str());
			ImGui::Text("  Stages: %c%c%c",
				(info.Stages | Graphics::EShaderType::Vertex   ? 'V' : ' '),
				(info.Stages | Graphics::EShaderType::Geometry ? 'G' : ' '),
				(info.Stages | Graphics::EShaderType::Pixel    ? 'P' : ' ')
				);
			ImGui::Text("  Found In: '%s'", info.FoundIn.c_str());
			ImGui::Text("  Compiled?: '%s'", BoolToString(info.Compiled));

			int j = 0;
			for (string error : info.ErrorsAndWarnings)
			{
				ImGui::Text("  Error/Warning [%d] = %s", j, error.c_str());
			}
		}
	}

}
