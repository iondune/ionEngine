#ifndef _CABBAGE_CORE_SLINE3_H_INCLUDED_
#define _CABBAGE_CORE_SLINE3_H_INCLUDED_

#include "SVector3.h"

class SLine3
{

public:

    SVector3f Start, End;

    SLine3()
    {}

    SLine3(SVector3f const & start, SVector3f const & end)
        : Start(start), End(end)
    {}

    SVector3f const getMiddle() const
    {
        return (Start + End) / 2.f;;;
    }

    SVector3f const getVector() const
    {
        return Start - End;
    }

    float const length() const
    {
        return getVector().length();
    }

};

#endif
