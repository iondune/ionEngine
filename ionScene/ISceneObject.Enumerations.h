#ifndef _CABBAGE_SCENE_ISCENEOBJECT_ENUMERATIONS_H_INCLUDED_
#define _CABBAGE_SCENE_ISCENEOBJECT_ENUMERATIONS_H_INCLUDED_

// Core
#include <ionEnum.h>


struct EDebugDataValues
{
	enum Domain
	{
		All = 0,
		Normals = 1,
		NormalColors = 2,
		Wireframe = 4
	};
};

typedef Enum<EDebugDataValues> EDebugData;



struct ERenderCategoryValues
{
	enum Domain
	{
		PreProcess,
		Default,
		Transparent,
		PostProcess,
		Count
	};
};

typedef Enum<ERenderCategoryValues> ERenderCategory;

#endif
