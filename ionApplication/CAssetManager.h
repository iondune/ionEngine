
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

		void Init(CGraphicsAPI * GraphicsAPI);

		SharedPointer<Graphics::IShaderProgram> LoadShader(string const & Name);
		SharedPointer<Graphics::ITexture2D> LoadTexture(string const & FileName, Graphics::ITexture::EMipMaps const MipMaps = Graphics::ITexture::EMipMaps::True);
		SharedPointer<Graphics::ITextureCubeMap> LoadCubeMapTexture(
			string const & FileNameLeft,
			string const & FileNameRight,
			string const & FileNameUp,
			string const & FileNameDown,
			string const & FileNameFront,
			string const & FileNameBack,
			Graphics::ITexture::EMipMaps const MipMaps = Graphics::ITexture::EMipMaps::True);
		Scene::CSimpleMesh * LoadMesh(string const & FileName);

		void AddAssetPath(string const & Path);
		void SetTexturePath(string const & Path);
		void SetShaderPath(string const & Path);
		void SetMeshPath(string const & Path);

	protected:

		SingletonPointer<CGraphicsAPI> GraphicsAPI;

		vector<string> AssetPaths;
		string TexturePath = "Textures/";
		string ShaderPath = "Shaders/";
		string MeshPath = "Meshes/";

	private:

		friend class Singleton<CAssetManager>;
		CAssetManager()
		{}

	};

}
