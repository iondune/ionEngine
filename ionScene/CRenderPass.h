
#pragma once

#include "ICamera.h"
#include "ILight.h"
#include "ISceneObject.h"


namespace ion
{
	namespace Scene
	{

		bool IsUniformNameArrayElement(string const & Label, int & Index, string & LHS, string & Remaining);

		class CRenderPass
		{

		public:

			CRenderPass(SharedPointer<Graphics::IGraphicsContext> GraphicsContext);
			virtual void SetRenderTarget(SharedPointer<Graphics::IRenderTarget> RenderTarget);

			virtual string const & GetName() const;
			virtual CGraphicsAPI * GetGraphicsAPI();
			virtual SharedPointer<Graphics::IGraphicsContext> GetGraphicsContext();

			virtual ICamera * GetActiveCamera();
			virtual ICamera const * GetActiveCamera() const;
			virtual void SetActiveCamera(ICamera * Camera);

			virtual void AddLight(ILight * Light);
			virtual void RemoveLight(ILight * Light);

			virtual void AddSceneObject(ISceneObject * SceneObject);
			virtual void RemoveSceneObject(ISceneObject * SceneObject);

			virtual void SetUniform(string const & Name, SharedPointer<Graphics::IUniform> Uniform);
			virtual void SetTexture(string const & Name, SharedPointer<Graphics::ITexture> Texture);

			virtual void Load();
			virtual void Draw();
			virtual void ReloadAll();

			virtual void PreparePipelineStateForRendering(SharedPointer<Graphics::IPipelineState> PipelineState, ISceneObject * SceneObject);
			virtual void SubmitPipelineStateForRendering(SharedPointer<Graphics::IPipelineState> PipelineState, ISceneObject * SceneObject, uint const InstanceCount = 1, uint const RenderCategory = 0);

		protected:

			ICamera * ActiveCamera = nullptr;
			set<ISceneObject *> SceneObjects;
			map<string, vector<ILight *>> Lights;

			map<string, SharedPointer<Graphics::IUniform>> Uniforms;
			map<string, SharedPointer<Graphics::ITexture>> Textures;

			vector<vector<std::tuple<ISceneObject *, SharedPointer<Graphics::IPipelineState>, uint>>> RenderQueue;
			string Name;

			SingletonPointer<CGraphicsAPI> GraphicsAPI;
			SharedPointer<Graphics::IGraphicsContext> GraphicsContext;
			SharedPointer<Graphics::IRenderTarget> RenderTarget;

			Graphics::CUniform<glm::mat4> uProjectionMatrix;
			Graphics::CUniform<glm::mat4> uViewMatrix;
			Graphics::CUniform<vec3f> uCameraPosition;
			Graphics::CUniform<glm::mat4> uModelMatrix;
			Graphics::CUniform<glm::mat4> uNormalMatrix;

		};

	}
}
