
#include "CGLGraphicsEngine.h"

#include "CGLGraphicsComponent.h"
#include "CShaderComponent.h"
#include "CMeshComponent.h"
#include "CTextureComponent.h"


CGLGraphicsEngine::CGLGraphicsEngine()
{
	RenderPasses.push_back(RenderPass{});
}

void CGLGraphicsEngine::Begin(CScene * Scene)
{
	ion::GL::Context::Clear({ion::GL::EBuffer::Color, ion::GL::EBuffer::Depth});
}

static void RecurseMesh(CSceneNode * SceneNode, CShader * Shader, vector<CDrawConfig *> & Definitions, SMeshNode * Node);

void CGLGraphicsEngine::Draw(CScene * Scene, ISceneNode * Node)
{
	CSceneNode * SceneNode = As<CSceneNode>(Node);

	if (SceneNode)
	{
		CGLGraphicsComponent * GraphicsComponent = SceneNode->RequireSingleComponent<CGLGraphicsComponent>();

		CShaderComponent * ShaderComponent = nullptr;
		CMeshComponent * MeshComponent = nullptr;
		CTextureComponent * TextureComponent = nullptr;
		SceneNode->ExpectSingleComponent<CShaderComponent>(ShaderComponent);
		SceneNode->ExpectSingleComponent<CMeshComponent>(MeshComponent);
		SceneNode->ExpectSingleComponent<CTextureComponent>(TextureComponent);

		bool NeedReset = false;
		if (ShaderComponent && ShaderComponent->IsDirty())
			NeedReset = true;
		if (MeshComponent && MeshComponent->IsDirty())
			NeedReset = true;
		if (TextureComponent && TextureComponent->IsDirty())
			NeedReset = true;

		if (! CheckMapAccess(GraphicsComponent->GetDrawConfigurations(), ShaderComponent->GetShader()) || NeedReset)
		{
			vector<CDrawConfig *> DrawDefinitions;

			if (MeshComponent)
			{
				RecurseMesh(SceneNode, ShaderComponent->GetShader(), DrawDefinitions, MeshComponent->GetMesh()->Root);
				MeshComponent->Clean();
			}

			auto ActiveUniforms = ShaderComponent->GetShader()->GetActiveUniforms();
			
			for (auto & ActiveUniform : ActiveUniforms)
			{
				auto Uniform = Scene->GetUniform(ActiveUniform.first);
				if (Uniform)
					for (auto & Definition : DrawDefinitions)
						Definition->AddUniform(ActiveUniform.first, Uniform);
			}
		
			for (auto & Uniform : ShaderComponent->GetUniforms())
				for (auto & Definition : DrawDefinitions)
					Definition->AddUniform(Uniform.first, Uniform.second);
			ShaderComponent->Clean();

			if (TextureComponent)
			{
				for (auto & Definition : DrawDefinitions)
				{
					for (uint i = 0; i < TextureComponent->GetTextureCount(); ++ i)
					{
						if (TextureComponent->GetTexture(i))
						{
							stringstream Label;
							Label << "Texture";
							Label << i;
							Definition->AddTexture(Label.str(), TextureComponent->GetTexture(i));
						}
					}
				}
				TextureComponent->Clean();
			}

			GraphicsComponent->GetDrawConfigurations()[ShaderComponent->GetShader()] = DrawDefinitions;
		}
		
		AddAtEnd(RenderPasses[0][ShaderComponent->GetShader()], GraphicsComponent->GetDrawConfigurations()[ShaderComponent->GetShader()]);
	}
}

static void RecurseMesh(CSceneNode * SceneNode, CShader * Shader, vector<CDrawConfig *> & Definitions, SMeshNode * Node)
{
	for (auto & Buffer : Node->Buffers)
	{
		CDrawConfig * DrawConfig = new CDrawConfig{Shader};

		DrawConfig->OfferVertexBuffer("Position", Buffer->VertexBuffers.Positions);
		DrawConfig->OfferVertexBuffer("Color", Buffer->VertexBuffers.Colors);
		DrawConfig->OfferVertexBuffer("Normal", Buffer->VertexBuffers.Normals);
		DrawConfig->OfferVertexBuffer("TexCoord", Buffer->VertexBuffers.TexCoords);
		DrawConfig->SetIndexBuffer(Buffer->VertexBuffers.Indices);

		DrawConfig->OfferUniform("Model", & SceneNode->GetTransformationUniform());
		DrawConfig->OfferUniform("Local", & Node->AbsoluteTransformation);

		Definitions.push_back(DrawConfig);
	}
	
	for (auto & Child : Node->GetChildren())
	{
		RecurseMesh(SceneNode, Shader, Definitions, Child);
	}
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
