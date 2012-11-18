#ifndef _CABBAGE_CORE_SLINE3_H_INCLUDED_
#define _CABBAGE_CORE_SLINE3_H_INCLUDED_

#include "SVector3.h"

template <typename T>
class SLine3
{

public:

    SVector3<T> Start, End;

    SLine3()
    {}

    SLine3(SVector3<T> const & start, SVector3<T> const & end)
        : Start(start), End(end)
    {}

    SVector3<T> const getMiddle() const
    {
        return (Start + End) / 2;
    }

    SVector3<T> const getVector() const
    {
        return Start - End;
    }

    T const length() const
    {
        return getVector().length();
    }

};

typedef SLine3<float> SLine3f;
typedef SLine3<double> SLine3d;
typedef SLine3<int> SLine3i;

#endif
