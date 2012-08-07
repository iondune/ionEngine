#ifndef _CABBAGE_SCENE_CPOINTLIGHTSCENEOBJECT_H_INCLUDED_
#define _CABBAGE_SCENE_CPOINTLIGHTSCENEOBJECT_H_INCLUDED_

#include "ISceneObject.h"
#include "CMeshLoader.h"

/*!
 */
class CPointLightSceneObject : public ISceneObject
{

protected:

	CMesh * SphereMesh;
	CMesh::SMeshBuffer * MeshBuffer;

	CShader * Shader;
	SColorAf Color;

public:

	CPointLightSceneObject(float const radius = 3.f, SColorAf const & color = SColorAf(1.f));

	virtual bool draw(IScene const * const scene, ERenderPass const Pass, bool const CullingEnabled);

	virtual void load(IScene const * const Scene, ERenderPass const Pass);

	virtual void setRadius(float const Radius);
	virtual void setScale(SVector3f const & scale);
	virtual void setColor(SVector3f const & color);

};

#endif
