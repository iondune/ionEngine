#ifndef _CABBAGE_SCENE_SVERTEX_H_INCLUDED_
#define _CABBAGE_SCENE_SVERTEX_H_INCLUDED_

#include "SVector3.h"
#include "SVector2.h"
#include "SColor.h"

class SVertex
{

public:

	SVector3f Position;
    SVector3f Normal;
	SVector2f TextureCoordinates;

	SColor Color;

};

#endif
