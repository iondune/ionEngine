
//! Instantiates all templates for code coverage purposes

#pragma once

#include <ionCore.h>


// ionClass.h

class SingletonInstantiate : public Singleton<SingletonInstantiate>
{};

template class Singleton<SingletonInstantiate>;
template class SingletonPointer<SingletonInstantiate>;


// ionComparison.h

template struct RoundingError<int>;
template struct RoundingError<unsigned int>;
template struct RoundingError<float>;
template struct RoundingError<double>;

template static bool Equals<int>(int const a, int const b, int const epsilon);
template static int const Maximum(int const & a, int const & b, int const & c, int const & d);
template static int const Minimum(int const & a, int const & b, int const & c, int const & d);
template static int const Max(int const & a, int const & b, int const & c, int const & d);
template static int const Min(int const & a, int const & b, int const & c, int const & d);


// ionTreeNode.h

class ITreeNodeInstantiate : public ITreeNode<ITreeNodeInstantiate>
{};

template class ITreeNode<ITreeNodeInstantiate>;
