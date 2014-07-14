
#include "CSceneNode.h"



CSceneNode::CSceneNode(CScene * Scene, ISceneNode * Parent)
: ISceneNode(Parent)
{
	this->Scene = Scene;
	TransformationUniform.Value = & AbsoluteTransformation;
}

void CSceneNode::Update()
{
	for (auto it : Components)
		it.second->Update(this);

	ISceneNode::Update();
}

void CSceneNode::Draw(IGraphicsEngine * Engine)
{
	if (Visible)
		Engine->Draw(this);
	
	ISceneNode::Draw(Engine);
}

CScene * CSceneNode::GetScene()
{
	return Scene;
}

CUniformReference<glm::mat4> & CSceneNode::GetTransformationUniform()
{
	return TransformationUniform;
}


CShader * CSceneNode::GetShader()
{
	CShaderComponent * ShaderComponent = RequireSingleComponent<CShaderComponent>();
	return ShaderComponent->GetShader();
}

CMesh * CSceneNode::GetMesh()
{
	CMeshComponent * MeshComponent = RequireSingleComponent<CMeshComponent>();
	return MeshComponent->GetMesh();
}

CTexture * CSceneNode::GetTexture(uint const Index)
{
	CTextureComponent * TextureComponent = RequireSingleComponent<CTextureComponent>();
	return TextureComponent->GetTexture(Index);
}


void CSceneNode::SetShader(CShader * Shader)
{
	CShaderComponent * ShaderComponent = RequireSingleComponent<CShaderComponent>();
	ShaderComponent->SetShader(Shader);
}

void CSceneNode::SetMesh(CMesh * Mesh)
{
	CMeshComponent * MeshComponent = RequireSingleComponent<CMeshComponent>();
	MeshComponent->SetMesh(Mesh);
}

void CSceneNode::SetTexture(uint const Index, CTexture * Texture)
{
	CTextureComponent * TextureComponent = RequireSingleComponent<CTextureComponent>();
	TextureComponent->SetTexture(Index, Texture);
}
