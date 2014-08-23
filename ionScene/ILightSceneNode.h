
#include "ISceneNode.h"


class ILightSceneNode : public ISceneNode
{

public:

	ILightSceneNode(ISceneNode * Parent);

	virtual map<CShader *, vector<CDrawConfig *>> PrepareDrawConfigurations(CDrawManager * DrawManager, IRenderPass * Pass);

	void SetRadius(float const Radius);
	void SetColor(color3f const & Color);

	float GetRadius() const;
	color3f GetColor() const;

private:

	float Radius = 10.f;
	color3f Color = Colors::White;

};
