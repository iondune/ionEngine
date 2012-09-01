#include "ISceneObject.h"


ISceneObject const * const ISceneObject::getParent() const
{
	return Parent;
}

std::list<ISceneObject *> const & ISceneObject::getChildren() const
{
	return Children;
}


void ISceneObject::addChild(ISceneObject * child)
{
	Children.push_back(child);
	child->Parent = this;
}

void ISceneObject::removeChild(ISceneObject * child)
{
	for (auto it = Children.begin(); it != Children.end(); ++ it)
	{
		if (* it == child)
		{
			Children.erase(it);
			child->Parent = 0;
			return;
		}
	}
}


void ISceneObject::setParent(ISceneObject * parent)
{
	if (Parent)
		Parent->removeChild(this);

	if (parent)
		parent->addChild(this);
}

void ISceneObject::removeAllChildren()
{
	Children.clear();
}
