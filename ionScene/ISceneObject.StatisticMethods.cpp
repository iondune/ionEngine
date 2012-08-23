#include "ISceneObject.h"


int ISceneObject::ObjectsCulled = 0;
int ISceneObject::TotalObjects = 0;
int ISceneObject::CullChecks = 0;

void ISceneObject::resetObjectCounts()
{
	ObjectsCulled = 0;
	TotalObjects = 0;
	CullChecks = 0;
}

int const ISceneObject::getObjectsCulled()
{
	return ObjectsCulled;
}

int const ISceneObject::getTotalObjects()
{
	return TotalObjects;
}

int const ISceneObject::getCullChecks()
{
	return CullChecks;
}
