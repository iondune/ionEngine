
#pragma once

#include <ionGL.h>
#include "IGraphicsEngine.h"
#include "CScene.h"


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

		ion::GL::Uniform * GetUniform(string const & Label)
		{
			return ConditionalMapAccess(Uniforms, Label);
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

	void Begin(CScene * Scene)
	{
		ion::GL::Context::Clear({ion::GL::EBuffer::Color, ion::GL::EBuffer::Depth});
	}
	
	void Finalize(CScene * Scene)
	{
		for (auto & Pass : RenderPasses)
		{
			for (auto & Element : Pass.Elements)
			{
				auto ActiveUniforms = Element.first->GetActiveUniforms();
				std::vector<string> RequiredUniforms;

				ion::GL::DrawContext Context(Element.first);

				for (auto & ActiveUniform : ActiveUniforms)
				{
					auto Uniform = Scene->GetUniform(ActiveUniform.first);
					if (Uniform)
						Context.BindUniform(ActiveUniform.first, Uniform);
					else
						RequiredUniforms.push_back(ActiveUniform.first);
				}

				for (auto & Definition : Element.second)
				{
					for (auto & RequiredUniform : RequiredUniforms)
					{
						auto Uniform = Definition.GetUniform(RequiredUniform);
						if (Uniform)
							Context.BindUniform(RequiredUniform, Uniform);
						else
							cerr << "Error! Unbound uniform " << RequiredUniform << endl;
					}

					Context.SetVertexArray(Definition.Array);
					Context.Draw();
				}
			}
		}
	}


	vector<SRenderPass> RenderPasses;

};
