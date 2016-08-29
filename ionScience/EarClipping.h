
#pragma once

#include <ionMath.h>


namespace ion
{

	float Determinant(vec2f const & u, vec3f const & v);
	bool IsPointInTriangle(vec2f const & a, vec2f const & b, vec2f const & c, vec2f const & point);
	bool IsPointInOrOnTriangle(vec2f const & a, vec2f const & b, vec2f const & c, vec2f const & point);

	struct STriangle2D
	{
		vec2f A, B, C;
	};

	vector<STriangle2D> TriangulateEarClipping(vector<vec2f> const & OriginalPoints);

}
