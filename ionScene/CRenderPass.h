
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

			CRenderPass(Graphics::IGraphicsAPI * GraphicsAPI);

			virtual string const & GetName() const;
			Graphics::IGraphicsAPI * GetGraphicsAPI();

			virtual ICamera * GetActiveCamera();
			virtual ICamera const * GetActiveCamera() const;
			virtual void SetActiveCamera(ICamera * Camera);

			virtual void AddLight(ILight * Light);
			//virtual void RemoveLight(ILight * Light);

			virtual void AddSceneObject(ISceneObject * SceneObject);
			virtual void RemoveSceneObject(ISceneObject * SceneObject);

			virtual void Load();
			virtual void Draw();

			virtual void PreparePipelineStateForRendering(Graphics::IPipelineState * PipelineState, ISceneObject * SceneObject);
			virtual void SubmitPipelineStateForRendering(Graphics::IPipelineState * PipelineState, ISceneObject * SceneObject);

		protected:

			ICamera * ActiveCamera = nullptr;
			set<ISceneObject *> SceneObjects;
			set<ILight *> Lights;
			map<string, Graphics::IUniform *> Uniforms;
			string Name;

			Graphics::CUniformValue<glm::mat4> uProjectionMatrix;
			Graphics::CUniformValue<glm::mat4> uViewMatrix;
			Graphics::CUniformValue<vec3f> uCameraPosition;
			Graphics::CUniformValue<glm::mat4> uModelMatrix;
			Graphics::CUniformValue<glm::mat4> uNormalMatrix;

			struct SLightUniformMatrixRow
			{
				vector<map<string, Graphics::IUniform *>> Entries;
				Graphics::CUniformValue<uint> CountUniform;
			};
			map<string, SLightUniformMatrixRow> LightUniformMatrix;

			void RebuildLightUniformMatrix();

			Graphics::IGraphicsAPI * GraphicsAPI = nullptr;

		};

	}
}
