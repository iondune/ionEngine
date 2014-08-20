
#include "CGLGraphicsEngine.h"


CGLGraphicsEngine::CGLGraphicsEngine()
{
	RenderPasses.push_back(RenderPass{});
}

void CGLGraphicsEngine::Begin(CScene * Scene)
{
	ion::GL::Context::Clear({ion::GL::EBuffer::Color, ion::GL::EBuffer::Depth});
}


void CGLGraphicsEngine::Draw(CScene * Scene, map<CShader *, vector<CDrawConfig *>> const & Configurations)
{
	for (auto Shader : Configurations)
		AddAtEnd(RenderPasses[0][Shader.first], Shader.second);
}

void CGLGraphicsEngine::Finalize(CScene * Scene)
{
	for (auto & Pass : RenderPasses)
	{
		for (auto & Shader : Pass)
		{
			if (! Shader.first)
				continue;

			ion::GL::DrawContext Context(Shader.first);

			for (auto & Element : Shader.second)
				Context.Draw(Element);
		}

		Pass.clear();
	}
}
