#ifndef _CABBAGE_SCENE_CDIRECTIONALLIGHTSCENEOBJECT_H_INCLUDED_
#define _CABBAGE_SCENE_CDIRECTIONALLIGHTSCENEOBJECT_H_INCLUDED_

#include "ISceneObject.h"
#include "CMeshLoader.h"

/*!
 */
class CDirectionalLightSceneObject : public ISceneObject
{

protected:

	CShader * Shader;
	SColor Color;
	SVector3f Direction;

public:

	CDirectionalLightSceneObject(SVector3f const direction, SColor const & color = SColor(1,1,1));

	virtual bool draw(IScene const * const scene, ERenderPass const Pass, bool const CullingEnabled);

	virtual void load(IScene const * const Scene, ERenderPass const Pass);

	virtual void setDirection(SVector3f const & direction);
	virtual void setColor(SVector3f const & color);

};

#endif
