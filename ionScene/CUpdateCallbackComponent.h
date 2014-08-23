
#pragma once

#include "CSceneNode.h"
#include "CDrawManager.h"


class CUpdateCallbackComponent : public ISceneNodeComponent
{

public:

	CUpdateCallbackComponent(std::function<void(CSceneNode *)> const & Callback);
	
	void Update(CSceneNode * Node);
	void Draw(CSceneNode * Node, CDrawManager * Engine);

private:

	std::function<void(CSceneNode *)> Callback;

};
