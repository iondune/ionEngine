
#pragma once

#include <ionScene/CSimpleMesh.h>
#include "SVolume.h"


struct SMarchingCubesPoint
{
	f32 Value = 0;
	vec3f Gradient;

	SMarchingCubesPoint()
	{}

	SMarchingCubesPoint(f32 const & value)
		: Value(value)
	{}
};

typedef SVolume<SMarchingCubesPoint> SMarchingCubesVolume;

void CalculateGradient(SMarchingCubesVolume & Volume);
ion::Scene::CSimpleMesh * MarchingCubes(SMarchingCubesVolume & Volume);

extern s32 const TriTable[256][16];
extern u32 const EdgeTable[256];
