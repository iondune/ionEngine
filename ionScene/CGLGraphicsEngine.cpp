
#include "CGLGraphicsEngine.h"
#include "CMeshComponent.h"


CGLGraphicsEngine::CGLGraphicsEngine()
{
	RenderPasses.push_back(SRenderPass{});
}

void CGLGraphicsEngine::Begin(CScene * Scene)
{
	ion::GL::Context::Clear({ion::GL::EBuffer::Color, ion::GL::EBuffer::Depth});
}

void RecurseAndDraw(CSceneNode * SceneNode, CMeshComponent * Component, vector<CGLGraphicsEngine::SDrawDefinition> & Definitions, SMeshNode * Node, vector<ion::GL::ImageTexture *> const & Textures);

void CGLGraphicsEngine::Draw(ISceneNode * Node)
{
	CSceneNode * SceneNode = As<CSceneNode>(Node);

	if (SceneNode)
	{
		CMeshComponent * MeshComponent = nullptr;
		int Count = SceneNode->ExpectSingleComponent<CMeshComponent>(MeshComponent);

		if (MeshComponent)
			RecurseAndDraw(SceneNode, MeshComponent, RenderPasses[0].Elements[MeshComponent->GetShader()], MeshComponent->GetMesh()->Root, MeshComponent->GetTextures());
	}
}

void RecurseAndDraw(CSceneNode * SceneNode, CMeshComponent * Component, vector<CGLGraphicsEngine::SDrawDefinition> & Definitions, SMeshNode * Node, vector<ion::GL::ImageTexture *> const & Textures)
{
	for (uint i = 0; i < Node->Buffers.size(); ++ i)
	{
		CGLGraphicsEngine::SDrawDefinition Definition{Node->Buffers[i]->ArrayObject};
		Definition.AddUniform("Model", SceneNode->GetTransformationUniform());
		Definition.AddUniform("Local", Node->AbsoluteTransformation);

		for (uint i = 0; i < Textures.size(); ++ i)
		{
			stringstream Label;
			Label << "Texture";
			Label << i;
			Definition.AddUniform(Label.str(), Component->GetTextureUniforms()[i]);
			Definition.Textures.push_back(Textures[i]);
		}

		Definitions.push_back(Definition);
	}
	
	for (auto & Child : Node->GetChildren())
	{
		RecurseAndDraw(SceneNode, Component, Definitions, Child, Textures);
	}
}

	
void CGLGraphicsEngine::Finalize(CScene * Scene)
{
	for (auto & Pass : RenderPasses)
	{
		for (auto & Element : Pass.Elements)
		{
			if (! Element.first)
				continue;

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

				for (uint i = 0; i < Definition.Textures.size(); ++ i)
				{
					Definition.Textures[i]->Activate(i);
				}

				Context.SetVertexArray(Definition.Array);
				Context.Draw();

				for (uint i = 0; i < Definition.Textures.size(); ++ i)
				{
					Definition.Textures[i]->Deactivate(i);
				}
			}
		}

		Pass.Elements.clear();
	}
}
