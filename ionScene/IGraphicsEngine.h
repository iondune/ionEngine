
#pragma once


class CScene;

class IGraphicsEngine
{

public:

	virtual void Begin(CScene * Scene) = 0;
	virtual void Finalize(CScene * Scene) = 0;

};
