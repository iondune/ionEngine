
#pragma once

#include <ionAsset.h>


class CScene;

class IGraphicsEngine
{

public:

	virtual void Begin(CScene * Scene) = 0;
	virtual void Draw(CScene * Scene, map<CShader *, vector<CDrawConfig *>> const & Configurations) = 0;
	virtual void Finalize(CScene * Scene) = 0;

};
