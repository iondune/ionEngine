
#pragma once

#include <ionCore.h>
#include <ionGL.h>
#include <ionAsset.h>

#include "ISceneNodeComponent.h"


class CGLGraphicsComponent : public ISceneNodeComponent
{

public:
	
	CGLGraphicsComponent();
	
	void Update(CSceneNode * Node);
	
	map<CShader *, CDrawConfig *> & GetRenderPasses();
	map<CShader *, CDrawConfig *> const & GetRenderPasses() const;

private:

	map<CShader *, CDrawConfig *> RenderPasses;

};
