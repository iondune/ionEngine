#ifdef _ION_SCENE_IRENDERPASS_H_INCLUDED_
#define _ION_SCENE_IRENDERPASS_H_INCLUDED_


class ISceneObject;

class IRenderPass
{

public:

	virtual void onPreDraw()
	{}

	virtual void onPostDraw()
	{}

	virtual void onPostEffects()
	{}

	virtual void onPreDrawObject(ISceneObject * Object)
	{}

	virtual void onPostDrawObject(ISceneObject * Object)
	{}

	virtual bool isEnabled()
	{
		return true;
	}

};

#endif
