
#pragma once


class CScene;
class ISceneNode;

class IGraphicsEngine
{

public:

	virtual void Begin(CScene * Scene) = 0;
	virtual void Draw(ISceneNode * Node) = 0;
	virtual void Finalize(CScene * Scene) = 0;

};
