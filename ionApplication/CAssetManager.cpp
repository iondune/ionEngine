
#include "CAssetManager.h"


namespace ion
{

	void CAssetManager::Init(Graphics::IGraphicsAPI * GraphicsAPI)
	{
		this->GraphicsAPI = GraphicsAPI;
	}

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
			Graphics::ITexture::EFormatComponents Format = Graphics::ITexture::EFormatComponents::R;
			switch (Image->GetChannels())
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
			SharedPointer<Graphics::ITexture2D> Texture = GraphicsAPI->CreateTexture2D(
				Image->GetSize(),
				Graphics::ITexture::EMipMaps::True,
				Format,
				Graphics::ITexture::EInternalFormatType::Fix8);
			Texture->Upload(
				Image->GetData(),
				Image->GetSize(),
				Format,
				Graphics::EScalarType::UnsignedInt8);
			return Texture;
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
