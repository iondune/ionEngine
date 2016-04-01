
#include "CAssetManager.h"


namespace ion
{

	void CAssetManager::Init()
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

	SharedPointer<Graphics::ITexture2D> CAssetManager::LoadTexture(string const & FileName)
	{
		if (! GraphicsAPI)
		{
			Log::Error("CAssetManager being used without being initialized, Texture '%s' will not be loaded.", FileName);
			return nullptr;
		}

		CImage * Image = CImage::Load(AssetPath + TexturePath + FileName);
		if (Image)
		{
			return GraphicsAPI->CreateTexture2D(Image);
		}
		else
		{
			return nullptr;
		}
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

}
