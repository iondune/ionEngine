
#pragma once

#include "CSceneNode.h"


class CUpdateCallbackComponent : public ISceneNodeComponent
{

public:

	CUpdateCallbackComponent(std::function<void(CSceneNode *)> const & Callback);
	
	void Update(CSceneNode * Node);
	void Draw(CSceneNode * Node, IGraphicsEngine * Engine);

private:

	std::function<void(CSceneNode *)> Callback;

};
