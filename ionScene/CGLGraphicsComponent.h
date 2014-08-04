
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
	
	map<CShader *, vector<CDrawConfig *>> & GetDrawConfigurations();
	map<CShader *, vector<CDrawConfig *>> const & GetDrawConfigurations() const;

	void Reset();

private:

	map<CShader *, vector<CDrawConfig *>> DrawConfigurations;

};
