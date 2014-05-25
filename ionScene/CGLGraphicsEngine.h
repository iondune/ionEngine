
#pragma once

#include <ionGL.h>
#include "IGraphicsEngine.h"


class CGLGraphicsEngine : public IGraphicsEngine, public Singleton<CGLGraphicsEngine>
{

public:

	struct SDrawDefinition
	{
		ion::GL::VertexArray * Array = 0;
		map<string, ion::GL::Uniform *> Uniforms;

		SDrawDefinition()
		{}

		SDrawDefinition(ion::GL::VertexArray * Array)
		{
			this->Array = Array;
		}

		SDrawDefinition & AddUniform(string const & Label, ion::GL::Uniform * Uniform)
		{
			Uniforms[Label] = Uniform;
			return *this;
		}
	};

	struct SRenderPass
	{
		map<ion::GL::Program *, vector<SDrawDefinition>> Elements;
	};


	CGLGraphicsEngine()
	{
		RenderPasses.push_back(SRenderPass{});
	}

	void Begin()
	{
		ion::GL::Context::Clear({ion::GL::EBuffer::Color, ion::GL::EBuffer::Depth});
	}
	
	void Finalize()
	{
		for (auto & Pass : RenderPasses)
		{
			for (auto & Element : Pass.Elements)
			{
				ion::GL::DrawContext context(Element.first);
				for (auto & Definition : Element.second)
				{
					for (auto & Uniform : Definition.Uniforms)
						context.BindUniform(Uniform.first, Uniform.second);

					context.SetVertexArray(Definition.Array);
					context.Draw();
				}
			}
		}
	}


	vector<SRenderPass> RenderPasses;

};
