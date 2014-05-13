
#if 0
#pragma once

// Core
#include <ionCore/ionSmartPtr.h>

// Scene
#include "ICameraSceneObject.h"


class IUniform;
class IAttribute;

class IScene
{

public:

	virtual ICameraSceneObject * const GetActiveCamera() = 0;
	virtual ICameraSceneObject const * const GetActiveCamera() const = 0;
	virtual void GetActiveCamera(ICameraSceneObject * const activeCamera) = 0;
	
	virtual sharedPtr<IAttribute const> const getAttribute(std::string const & label) const = 0;
	virtual sharedPtr<IUniform const> const getUniform(std::string const & label) const = 0;

	virtual void update() = 0;
	virtual void load(sharedPtr<IRenderPass> const Pass) = 0;
	virtual void draw(sharedPtr<IRenderPass> const Pass) = 0;

};
#endif
