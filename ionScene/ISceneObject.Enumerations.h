
#pragma once


enum class EDebugData
{
	All = 0,
	Normals = 1,
	NormalColors = 2,
	Wireframe = 4
};

enum class ERenderCategory
{
	PreProcess,
	Default,
	Transparent,
	PostProcess,
	Count
};
