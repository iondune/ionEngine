#ifndef _CABBAGE_SCENE_ISCENE_H_INCLUDED_
#define _CABBAGE_SCENE_ISCENE_H_INCLUDED_

// Core
#include <boost/shared_ptr.hpp>

// Scene
#include "ICameraSceneObject.h"


class IUniform;
class IAttribute;

class IScene
{

public:

	virtual ICameraSceneObject * const getActiveCamera() = 0;
	virtual ICameraSceneObject const * const getActiveCamera() const = 0;
	virtual void setActiveCamera(ICameraSceneObject * const activeCamera) = 0;
	
	virtual smartPtr<IAttribute const> const getAttribute(std::string const & label) const = 0;
	virtual smartPtr<IUniform const> const getUniform(std::string const & label) const = 0;

	virtual void update() = 0;
	virtual void load(smartPtr<IRenderPass> const Pass) = 0;
	virtual void draw(smartPtr<IRenderPass> const Pass) = 0;

};

#endif
