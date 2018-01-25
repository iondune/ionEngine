
#pragma once

#include "ISceneObject.h"


namespace ion
{

	namespace Scene
	{

		class CLineSceneObject : public ISceneObject
		{

		public:

			CLineSceneObject();
			~CLineSceneObject();

			virtual void Load(CRenderPass * RenderPass);
			virtual void Draw(CRenderPass * RenderPass);

			virtual void SetShader(SharedPointer<Graphics::IShader> Shader);
			virtual void SetFeatureEnabled(Graphics::EDrawFeature const Feature, bool const Enabled);
			virtual void SetRenderCategory(int const Category);

			void ResetLines();
			void AddLine(vec3f const & A, vec3f const & B, color3f const & Color);

		protected:

			vector<uint> Indices;
			vector<float> Vertices;
			bool DataNeedsUpload = true;

			size_t IndexCounter = 0;
			int RenderCategory = 0;

			SharedPointer<Graphics::IPipelineState> PipelineState;
			SharedPointer<Graphics::IShader> Shader;

			SharedPointer<Graphics::IIndexBuffer> IndexBuffer;
			SharedPointer<Graphics::IVertexBuffer> VertexBuffer;

		};

	}

}
