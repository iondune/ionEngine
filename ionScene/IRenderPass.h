#ifndef _ION_SCENE_IRENDERPASS_H_INCLUDED_
#define _ION_SCENE_IRENDERPASS_H_INCLUDED_


class ISceneObject;

class IRenderPass
{

public:

	virtual void onPreDrawObject(ISceneObject * Object)
	{}

	virtual void onPostDrawObject(ISceneObject * Object)
	{}

};

#endif
