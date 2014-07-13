
#pragma once

#include "ISceneNode.h"


class CScene;
class CSceneNode;


class ISceneNodeComponent
{

public:

	virtual void Update(CSceneNode * Node) = 0;

};

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

protected:

	CScene * Scene;

	CUniformReference<glm::mat4> TransformationUniform;

};
