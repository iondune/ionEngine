
#include "ISceneNode.h"


class ILightSceneNode : public ISceneNode
{

public:

	ILightSceneNode(ISceneNode * Parent);

	virtual map<CShader *, vector<CDrawConfig *>> PrepareDrawConfigurations(CDrawManager * DrawManager, IRenderPass * Pass);

};
