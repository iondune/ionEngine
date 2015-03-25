
#pragma once

#include <ionMath.h>


class SVertex
{

public:

	SVertex();
	SVertex(vec3f const & position,
		vec3f const & normal = vec3f(),
		vec2f const & texture = vec2f(),
		color4f const & color = color4f());

	vec3f Position;
	vec3f Normal;
	vec2f TextureCoordinates;

	color4f Color;

	vec2i BoneIndices = vec2i(-1);
	vec2f BoneWeights = 0;

};
