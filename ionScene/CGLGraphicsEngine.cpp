
#include "CGLGraphicsEngine.h"
#include "CShaderComponent.h"
#include "CMeshComponent.h"
#include "CTextureComponent.h"


CGLGraphicsEngine::CGLGraphicsEngine()
{
	RenderPasses.push_back(SRenderPass{});
}

void CGLGraphicsEngine::Begin(CScene * Scene)
{
	ion::GL::Context::Clear({ion::GL::EBuffer::Color, ion::GL::EBuffer::Depth});
}

static void RecurseMesh(CSceneNode * SceneNode, CMeshComponent * Component, vector<CGLGraphicsEngine::SDrawDefinition> & Definitions, SMeshNode * Node);

void CGLGraphicsEngine::Draw(ISceneNode * Node)
{
	CSceneNode * SceneNode = As<CSceneNode>(Node);

	if (SceneNode)
	{
		CShaderComponent * ShaderComponent = nullptr;
		CMeshComponent * MeshComponent = nullptr;
		CTextureComponent * TextureComponent = nullptr;
		
		SceneNode->ExpectSingleComponent<CShaderComponent>(ShaderComponent);
		SceneNode->ExpectSingleComponent<CMeshComponent>(MeshComponent);
		SceneNode->ExpectSingleComponent<CTextureComponent>(TextureComponent);

		if (MeshComponent)
			RecurseMesh(SceneNode, MeshComponent, RenderPasses[0].Elements[ShaderComponent->GetShader()], MeshComponent->GetMesh()->Root);
		
		if (TextureComponent)
		{
			for (auto & Definition : RenderPasses[0].Elements[ShaderComponent->GetShader()])
			{
				for (uint i = 0; i < TextureComponent->GetTextureCount(); ++ i)
				{
					stringstream Label;
					Label << "Texture";
					Label << i;
					Definition.AddUniform(Label.str(), TextureComponent->GetTextureUniform(i));
					Definition.Textures.push_back(TextureComponent->GetTexture(i)->GetHandle());
				}
			}
		}
	}
}

static void RecurseMesh(CSceneNode * SceneNode, CMeshComponent * Component, vector<CGLGraphicsEngine::SDrawDefinition> & Definitions, SMeshNode * Node)
{
	for (uint i = 0; i < Node->Buffers.size(); ++ i)
	{
		CGLGraphicsEngine::SDrawDefinition Definition{Node->Buffers[i]->ArrayObject};
		Definition.AddUniform("Model", SceneNode->GetTransformationUniform());
		Definition.AddUniform("Local", Node->AbsoluteTransformation);

		Definitions.push_back(Definition);
	}
	
	for (auto & Child : Node->GetChildren())
	{
		RecurseMesh(SceneNode, Component, Definitions, Child);
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
