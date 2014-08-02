
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
			static_cast<ITreeNode<Implementation> *>(Parent)->Children.erase(static_cast<Implementation *>(this));

		Parent = parent;

		if (Parent)
			static_cast<ITreeNode<Implementation> *>(parent)->Children.insert(static_cast<Implementation *>(this));
	}

	void RemoveAllChildren()
	{
		for (auto & Child : Children)
			Child->Parent = 0;
		Children.clear();
	}
	
	void Remove()
	{
		delete this;
	}

	template <typename Return>
	void RecurseOnChildren(Return (Implementation::* Function)())
	{
		for (auto Child : Children)
			(Child->*Function)();
	}

	template <typename Return, typename P1>
	void RecurseOnChildren(Return (Implementation::* Function)(P1), P1 p1)
	{
		for (auto Child : Children)
			(Child->*Function)(p1);
	}

	template <typename Return, typename P1, typename P2>
	void RecurseOnChildren(Return (Implementation::* Function)(P1, P2), P1 p1, P2 p2)
	{
		for (auto Child : Children)
			(Child->*Function)(p1, p2);
	}

	virtual ~ITreeNode()
	{
		SetParent(0);
	}

protected:

	ITreeNode()
		: Parent()
	{}

	Implementation * Parent;
	std::set<Implementation *> Children;

};


/*!
	Variant of ITreeNode that doesn't require a single parent relationship.
*/
template <typename Implementation>
class IMultiTreeNode
{

public:

	std::set<Implementation *> const & GetChildren() const
	{
		return Children;
	}

	void AddChild(Implementation * Child)
	{
		Children.insert(static_cast<Implementation *>(Child));
	}

	void RemoveChild(Implementation * Child)
	{
		Children.erase(static_cast<Implementation *>(Child));
	}

	void RemoveAllChildren()
	{
		Children.clear();
	}

	template <typename Return>
	void RecurseOnChildren(Return (Implementation::* Function)())
	{
		for (auto Child : Children)
			(Child->*Function)();
	}

	template <typename Return, typename P1>
	void RecurseOnChildren(Return (Implementation::* Function)(P1), P1 p1)
	{
		for (auto Child : Children)
			(Child->*Function)(p1);
	}

	template <typename Return, typename P1, typename P2>
	void RecurseOnChildren(Return (Implementation::* Function)(P1, P2), P1 p1, P2 p2)
	{
		for (auto Child : Children)
			(Child->*Function)(p1, p2);
	}

protected:

	IMultiTreeNode()
	{}

	std::set<Implementation *> Children;

};
