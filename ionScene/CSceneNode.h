
#pragma once

#include "ISceneNode.h"
#include "ISceneNodeComponent.h"

#include "CShaderComponent.h"
#include "CMeshComponent.h"
#include "CTextureComponent.h"


class CScene;

class CSceneNode : public ISceneNode, public IEntity<ISceneNodeComponent>
{

public:

	//! Constructor
	CSceneNode(CScene * Scene, ISceneNode * Parent);

	//! Perform pre-draw update
	virtual void Update();

	//! Perform draw
	virtual void Draw(IGraphicsEngine * Engine);

	//! Scene accessor
	CScene * GetScene();

	//! TransformationUniform accessor
	CUniformReference<glm::mat4> & GetTransformationUniform();
	
	CShader * GetShader();
	CMesh * GetMesh();
	CTexture * GetTexture(uint const Index);

	void SetShader(CShader * Shader);
	void SetMesh(CMesh * Mesh);
	void SetTexture(uint const Index, CTexture * Texture);

protected:

	CScene * Scene;

	CUniformReference<glm::mat4> TransformationUniform;

};
