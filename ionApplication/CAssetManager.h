
#pragma once

#include <ionCore.h>
#include <ionFramework.h>
#include <ionGraphics.h>
#include <ionWindow.h>
#include <ionScene.h>


namespace ion
{
	
	class CAssetManager : public Singleton<CAssetManager>
	{

	public:

		void Init(Graphics::IGraphicsAPI * GraphicsAPI);

		SharedPointer<Graphics::IShaderProgram> LoadShader(string const & Name);
		SharedPointer<Graphics::ITexture2D> LoadTexture(string const & FileName);

		void SetAssetPath(string const & Path);
		void SetTexturePath(string const & Path);
		void SetShaderPath(string const & Path);

	protected:

		Graphics::IGraphicsAPI * GraphicsAPI = nullptr;

		string AssetPath;
		string TexturePath;
		string ShaderPath;

	private:

		friend class Singleton<CAssetManager>;
		CAssetManager()
		{}

	};

}
