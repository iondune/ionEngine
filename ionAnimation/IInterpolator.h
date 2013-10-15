
#pragma once

#include <ionCore.h>

#include "IPath.h"


template <typename TPathNode>
class IInterpolator
{

public:

	virtual TPathNode const interpolate(IPath<TPathNode> const & Path, s32 const Index, float const Mu) = 0;

};
