
//! Instantiates all templates for code coverage purposes

#pragma once

#include <ionCore.h>


// ionClass.h

class Base
{
public:
	virtual void foo() = 0;
};

class Derived : Base
{};

template bool InstanceOf<Derived, Base>(Base * Object);
template bool InstanceOf<Derived, Base>(Base & Object);
template Derived * As<Derived, Base>(Base * Object);
template Derived const * As<Derived, Base>(Base const * Object);
template Derived & As<Derived, Base>(Base & Object);
template Derived const & As<Derived, Base>(Base const & Object);


class SingletonInstantiate : public Singleton<SingletonInstantiate>
{};

template class Singleton<SingletonInstantiate>;
template class SingletonPointer<SingletonInstantiate>;


// ionComparison.h

template struct RoundingError<int>;

template static bool Equals<int>(int const a, int const b, int const epsilon);
template static int Maximum(int const & a, int const & b);
template static int const Maximum(int const & a, int const & b, int const & c);
template static int const Maximum(int const & a, int const & b, int const & c, int const & d);
template static int Minimum(int const & a, int const & b);
template static int const Minimum(int const & a, int const & b, int const & c);
template static int const Minimum(int const & a, int const & b, int const & c, int const & d);
template static int const Max(int const & a, int const & b);
template static int const Max(int const & a, int const & b, int const & c);
template static int const Max(int const & a, int const & b, int const & c, int const & d);
template static int const Min(int const & a, int const & b);
template static int const Min(int const & a, int const & b, int const & c);
template static int const Min(int const & a, int const & b, int const & c, int const & d);


// ionComponent.h

class Component
{};

template class IEntity<Component>;
template int IEntity<Component>::GetComponentCount<Component>() const;
template pair<typename multimap<Type, Component *>::iterator, typename multimap<Type, Component *>::iterator> IEntity<Component>::GetComponents<Component>();
template Component * IEntity<Component>::AddComponent(Component * Component);
template int IEntity<Component>::ExpectSingleComponent(Component * & Component);
template Component * IEntity<Component>::RequireSingleComponent();


// ionSmartPtr.h

template static sharedPtr<Base> sharedNew(Base * const t);


// ionStandardLibrary.h

template int * ConditionalMapAccess(map<int, int *> const & Map, int const Key);
template bool CheckMapAccess(map<int, int> const & Map, int const Key);
template bool TryMapAccess(map<int, int> const & Map, int const Key, int & Value);
template void AddAtEnd(vector<int> & A, vector<int> const & B);


// ionTreeNode.h

class ITreeNodeInstantiate : public ITreeNode<ITreeNodeInstantiate>
{};

template class ITreeNode<ITreeNodeInstantiate>;
template void ITreeNode<ITreeNodeInstantiate>::RecurseOnChildren<int>(int (ITreeNodeInstantiate::* Function)());
template void ITreeNode<ITreeNodeInstantiate>::RecurseOnChildren<int, int>(int (ITreeNodeInstantiate::* Function)(int), int p1);
template void ITreeNode<ITreeNodeInstantiate>::RecurseOnChildren<int, int, int>(int (ITreeNodeInstantiate::* Function)(int, int), int p1, int p2);

template class IMultiTreeNode<ITreeNodeInstantiate>;
template void IMultiTreeNode<ITreeNodeInstantiate>::RecurseOnChildren<int>(int (ITreeNodeInstantiate::* Function)());
template void IMultiTreeNode<ITreeNodeInstantiate>::RecurseOnChildren<int, int>(int (ITreeNodeInstantiate::* Function)(int), int p1);
template void IMultiTreeNode<ITreeNodeInstantiate>::RecurseOnChildren<int, int, int>(int (ITreeNodeInstantiate::* Function)(int, int), int p1, int p2);


// ionUtils.h

template static int const Clamp<int>(int const & v, int const & min, int const & max);
template static int const Sq<int>(int const & a);
template static int const Average<int>(int const & a, int const & b);
template static int const Average<int>(int const & a, int const & b, int const & c);
template static int const Average<int>(int const & a, int const & b, int const & c, int const & d);
template s32 Sign<int>(int const & val);
