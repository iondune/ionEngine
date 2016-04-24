
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

	SharedPointer<Graphics::ITexture2D> CAssetManager::LoadTexture(string const & FileName, Graphics::ITexture::EMipMaps const MipMaps)
	{
		if (! GraphicsAPI)
		{
			Log::Error("CAssetManager being used without being initialized, Texture '%s' will not be loaded.", FileName);
			return nullptr;
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

	Scene::CSimpleMesh * CAssetManager::LoadMesh(string const & FileName)
	{
		if (! GraphicsAPI)
		{
			Log::Error("CAssetManager being used without being initialized, Texture '%s' will not be loaded.", FileName);
			return nullptr;
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

	void CAssetManager::SetAssetPath(string const & Path)
	{
		AssetPath = Path + "/";
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
