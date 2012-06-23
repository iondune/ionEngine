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
	
	virtual boost::shared_ptr<IAttribute const> const getAttribute(std::string const & label) const = 0;
	virtual boost::shared_ptr<IUniform const> const getUniform(std::string const & label) const = 0;

};

#endif
