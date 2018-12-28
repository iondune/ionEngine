
#pragma once

#include <ionMath.h>


namespace ion
{

	float Determinant(vec2f const & u, vec2f const & v);
	bool IsPointInTriangle(vec2f const & a, vec2f const & b, vec2f const & c, vec2f const & point);
	bool IsPointInOrOnTriangle(vec2f const & a, vec2f const & b, vec2f const & c, vec2f const & point);

	double Determinant(vec2d const & u, vec2d const & v);
	bool IsPointInTriangle(vec2d const & a, vec2d const & b, vec2d const & c, vec2d const & point);
	bool IsPointInOrOnTriangle(vec2d const & a, vec2d const & b, vec2d const & c, vec2d const & point);

	template <typename T>
	struct STriangle2D
	{
		vec2<T> A, B, C;
	};

	vector<STriangle2D<float>> TriangulateEarClipping(vector<vec2f> const & OriginalPoints);
	vector<STriangle2D<double>> TriangulateEarClipping(vector<vec2d> const & OriginalPoints);

}
