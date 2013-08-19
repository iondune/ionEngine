
#pragma once

#include <set>


class ITreeNode
{

public:

	ITreeNode const * const GetParent() const
	{
		return Parent;
	}

	std::set<ITreeNode *> const & GetChildren() const
	{
		return Children;
	}

	void AddChild(ITreeNode * child)
	{
		child->SetParent(this);
	}

	void RemoveChild(ITreeNode * child)
	{
		child->SetParent(0);
	}

	void SetParent(ITreeNode * parent)
	{
		if (Parent)
			Parent->Children.erase(this);
		
		Parent = parent;

		if (Parent)
			Parent->Children.insert(this);
	}

	void RemoveAllChildren()
	{
		for (auto Child : Children)
			Child->Parent = 0;
		Children.clear();
	}

protected:

	ITreeNode * Parent;
	std::set<ITreeNode *> Children;

};
