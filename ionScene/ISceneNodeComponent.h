
#pragma once


class CSceneNode;


class ISceneNodeComponent
{

public:

	virtual void Update(CSceneNode * Node) = 0;

};
