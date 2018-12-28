
#pragma once

#include "ionTypes.h"


namespace ion
{

	/*!
	\brief Variant of ITreeNode that doesn't require a single parent relationship.
	\ingroup ionCode
	*/
	template <typename Implementation>
	class IMultiTreeNode
	{

	public:

		set<Implementation *> const & GetChildren() const
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
		void RecurseOnChildren(Return(Implementation::* Function)())
		{
			for (auto Child : Children)
				(Child->*Function)();
		}

		template <typename Return, typename P1>
		void RecurseOnChildren(Return(Implementation::* Function)(P1), P1 p1)
		{
			for (auto Child : Children)
				(Child->*Function)(p1);
		}

		template <typename Return, typename P1, typename P2>
		void RecurseOnChildren(Return(Implementation::* Function)(P1, P2), P1 p1, P2 p2)
		{
			for (auto Child : Children)
				(Child->*Function)(p1, p2);
		}

	protected:

		IMultiTreeNode()
		{}

		set<Implementation *> Children;

	};

}
