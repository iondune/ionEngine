
#pragma once

#include <set>
#include <type_traits>


/*!
	Abstract Node in a generic tree structure.

	Note that a static_cast to TreeNode<Implementation> is sometimes needed
	for compilation in VS2012 where Implementation has 'uses' for Children
	or Parent since these fields will then have protected access in the 
	subclass.
*/
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
		if (child->Parent == this)
			child->SetParent(0);
	}

	void SetParent(Implementation * parent)
	{
		if (Parent)
			static_cast<ITreeNode<Implementation> *>(parent)->Children.erase(static_cast<Implementation *>(this));

		Parent = parent;

		if (Parent)
			static_cast<ITreeNode<Implementation> *>(parent)->Children.insert(static_cast<Implementation *>(this));
	}

	void RemoveAllChildren()
	{
		for (auto it = Children.begin(); it != Children.end(); ++ it)
			(*it)->Parent = 0;
		Children.clear();
	}

protected:

	ITreeNode()
		: Parent()
	{}

	Implementation * Parent;
	std::set<Implementation *> Children;

};
