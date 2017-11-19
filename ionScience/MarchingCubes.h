
#pragma once

#include <ionScene/CSimpleMesh.h>
#include "SVolume.h"


namespace ion
{

	struct SMarchingCubesPoint
	{
		float Value = 0;
		vec3f Gradient;

		SMarchingCubesPoint()
		{}

		SMarchingCubesPoint(float const & value)
			: Value(value)
		{}
	};

	typedef SVolume<SMarchingCubesPoint> SMarchingCubesVolume;

	void CalculateGradient(SMarchingCubesVolume & Volume);
	ion::Scene::CSimpleMesh * MarchingCubes(SMarchingCubesVolume & Volume);

	extern int const TriTable[256][16];
	extern uint const EdgeTable[256];

}
