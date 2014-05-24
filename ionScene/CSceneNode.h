
#pragma once

#include "ISceneNode.h"


class CSceneNode : public ISceneNode
{

public:

	/////////////////////
	// General Methods //
	/////////////////////

	CSceneNode(ISceneNode * Parent);

	//! Perform pre-draw update
	virtual void Update();

	//! Perform draw
	virtual void Draw();


	/////////////////////////////
	// Component/Entity System //
	/////////////////////////////

	class IComponent
	{

	public:

		virtual void Update(CSceneNode * Node) = 0;
		virtual void Draw(CSceneNode * Node) = 0;

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

	map<Type, IComponent *> Components;

};
