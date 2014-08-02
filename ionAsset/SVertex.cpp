
#include "SVertex.h"


SVertex::SVertex()
{}

SVertex::SVertex(vec3f const & position,
	vec3f const & normal,
	vec2f const & texture,
	color4f const & color)
{
	Position = position;
	Normal = normal;
	TextureCoordinates = texture;
	Color = color;
}
