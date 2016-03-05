
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

			CRenderPass(Graphics::IGraphicsAPI * GraphicsAPI, SharedPtr<Graphics::IGraphicsContext> GraphicsContext);
			virtual void SetRenderTarget(SharedPtr<Graphics::IRenderTarget> RenderTarget);

			virtual string const & GetName() const;
			virtual Graphics::IGraphicsAPI * GetGraphicsAPI();
			virtual SharedPtr<Graphics::IGraphicsContext> GetGraphicsContext();

			virtual ICamera * GetActiveCamera();
			virtual ICamera const * GetActiveCamera() const;
			virtual void SetActiveCamera(ICamera * Camera);

			virtual void AddLight(ILight * Light);
			//virtual void RemoveLight(ILight * Light);

			virtual void AddSceneObject(ISceneObject * SceneObject);
			virtual void RemoveSceneObject(ISceneObject * SceneObject);

			virtual void Load();
			virtual void Draw();

			virtual void PreparePipelineStateForRendering(SharedPtr<Graphics::IPipelineState> PipelineState, ISceneObject * SceneObject);
			virtual void SubmitPipelineStateForRendering(SharedPtr<Graphics::IPipelineState> PipelineState, ISceneObject * SceneObject, uint const InstanceCount = 1, uint const RenderCategory = 0);

		protected:

			ICamera * ActiveCamera = nullptr;
			set<ISceneObject *> SceneObjects;
			set<ILight *> Lights;
			map<string, SharedPtr<Graphics::IUniform>> Uniforms;
			vector<vector<std::tuple<ISceneObject *, SharedPtr<Graphics::IPipelineState>, uint>>> RenderQueue;
			string Name;

			Graphics::IGraphicsAPI * GraphicsAPI = nullptr;
			std::shared_ptr<Graphics::IGraphicsContext> GraphicsContext;
			std::shared_ptr<Graphics::IRenderTarget> RenderTarget;

			SharedPtr<Graphics::CUniformValue<glm::mat4>> uProjectionMatrix = std::make_shared<Graphics::CUniformValue<glm::mat4>>();
			SharedPtr<Graphics::CUniformValue<glm::mat4>> uViewMatrix = std::make_shared<Graphics::CUniformValue<glm::mat4>>();
			SharedPtr<Graphics::CUniformValue<vec3f>> uCameraPosition = std::make_shared<Graphics::CUniformValue<vec3f>>();
			SharedPtr<Graphics::CUniformValue<glm::mat4>> uModelMatrix = std::make_shared<Graphics::CUniformValue<glm::mat4>>();
			SharedPtr<Graphics::CUniformValue<glm::mat4>> uNormalMatrix = std::make_shared<Graphics::CUniformValue<glm::mat4>>();

			struct SLightUniformMatrixRow
			{
				vector<map<string, SharedPtr<Graphics::IUniform>>> Entries;
				SharedPtr<Graphics::CUniformValue<uint>> CountUniform = std::make_shared<Graphics::CUniformValue<uint>>(0);
			};
			map<string, SLightUniformMatrixRow> LightUniformMatrix;

			void RebuildLightUniformMatrix();


		};

	}
}
