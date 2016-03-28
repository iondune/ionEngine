
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
			//virtual void RemoveLight(ILight * Light);

			virtual void AddSceneObject(ISceneObject * SceneObject);
			virtual void RemoveSceneObject(ISceneObject * SceneObject);

			virtual void Load();
			virtual void Draw();

			virtual void PreparePipelineStateForRendering(SharedPointer<Graphics::IPipelineState> PipelineState, ISceneObject * SceneObject);
			virtual void SubmitPipelineStateForRendering(SharedPointer<Graphics::IPipelineState> PipelineState, ISceneObject * SceneObject, uint const InstanceCount = 1, uint const RenderCategory = 0);

		protected:

			ICamera * ActiveCamera = nullptr;
			set<ISceneObject *> SceneObjects;
			set<ILight *> Lights;
			map<string, SharedPointer<Graphics::IUniform>> Uniforms;
			vector<vector<std::tuple<ISceneObject *, SharedPointer<Graphics::IPipelineState>, uint>>> RenderQueue;
			string Name;

			SingletonPointer<CGraphicsAPI> GraphicsAPI;
			SharedPointer<Graphics::IGraphicsContext> GraphicsContext;
			SharedPointer<Graphics::IRenderTarget> RenderTarget;

			SharedPointer<Graphics::CUniformValue<glm::mat4>> uProjectionMatrix = MakeShared<Graphics::CUniformValue<glm::mat4>>();
			SharedPointer<Graphics::CUniformValue<glm::mat4>> uViewMatrix = MakeShared<Graphics::CUniformValue<glm::mat4>>();
			SharedPointer<Graphics::CUniformValue<vec3f>> uCameraPosition = MakeShared<Graphics::CUniformValue<vec3f>>();
			SharedPointer<Graphics::CUniformValue<glm::mat4>> uModelMatrix = MakeShared<Graphics::CUniformValue<glm::mat4>>();
			SharedPointer<Graphics::CUniformValue<glm::mat4>> uNormalMatrix = MakeShared<Graphics::CUniformValue<glm::mat4>>();

			struct SLightUniformMatrixRow
			{
				vector<map<string, SharedPointer<Graphics::IUniform>>> Entries;
				SharedPointer<Graphics::CUniformValue<int>> CountUniform = std::make_shared<Graphics::CUniformValue<int>>(0);
			};
			map<string, SLightUniformMatrixRow> LightUniformMatrix;

			void RebuildLightUniformMatrix();


		};

	}
}
