
#pragma once

#include <set>
#include <type_traits>


template <typename Implementation>
class ITreeNode
{

	// To Do : Why doesn't this work?
	//static_assert(std::is_base_of<ITreeNode<Implementation>, Implementation>::value, "ITreeNode<Implementation> must be a base of implementation type.");

public:

	Implementation const * const GetParent() const
	{
		return Parent;
	}

	std::set<Implementation *> const & GetChildren() const
	{
		return Children;
	}

	void AddChild(Implementation * child)
	{
		child->SetParent(static_cast<Implementation *>(this));
	}

	void RemoveChild(Implementation * child)
	{
		child->SetParent(0);
	}

	void SetParent(Implementation * parent)
	{
		if (Parent)
			Parent->Children.erase(static_cast<Implementation *>(this));
		
		Parent = parent;

		if (Parent)
			Parent->Children.insert(static_cast<Implementation *>(this));
	}

	void RemoveAllChildren()
	{
		for (auto Child : Children)
			Child->Parent = 0;
		Children.clear();
	}

protected:

	ITreeNode()
		: Parent()
	{}

	Implementation * Parent;
	std::set<Implementation *> Children;

};
