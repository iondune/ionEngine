
#pragma once

#include <ionAsset/CMesh.h>
#include "SVolume.h"


struct SMarchingCubesPoint
{
	f32 Value;
	f32 Color;
	vec3f Gradient;
};

typedef SVolume<SMarchingCubesPoint> SMarchingCubesVolume;

void CalculateGradient(SMarchingCubesVolume & Volume);
CMesh * MarchingCubes(SMarchingCubesVolume & Volume);
