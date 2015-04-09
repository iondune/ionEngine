
#pragma once

#include <ionScene.h>


class CSkinnedAnimation
{

public:

	struct SKeyframe
	{
		vec3f Rotation;
	};

protected:

	map<CMeshJoint *, vector<SKeyframe>> Keyframes;

};
