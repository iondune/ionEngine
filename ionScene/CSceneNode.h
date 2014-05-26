
#pragma once

#include "ISceneNode.h"


class CScene;

class CSceneNode : public ISceneNode
{

public:

	/////////////////////
	// General Methods //
	/////////////////////

	CSceneNode(CScene * Scene, ISceneNode * Parent);

	//! Perform pre-draw update
	virtual void Update();

	//! Perform draw
	virtual void Draw(IGraphicsEngine * Engine);

	CScene * GetScene();


	/////////////////////////////
	// Component/Entity System //
	/////////////////////////////

	class IComponent
	{

	public:

		virtual void Update(CSceneNode * Node) = 0;
		virtual void Draw(CSceneNode * Node, IGraphicsEngine * Engine) = 0;

	};

	template <typename T>
	void AddComponent(T * Component)
	{
		Components[typeid(T)] = Component;
	}

	template <typename T>
	IComponent * GetComponent()
	{
		return ConditionalMapAccess(Components, typeid(T));
	}

protected:

	CScene * Scene;
	map<Type, IComponent *> Components;

};
