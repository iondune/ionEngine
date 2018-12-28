
#include "EarClipping.h"


namespace ion
{

	float Determinant(vec2f const & u, vec2f const & v)
	{
		return u.X*v.Y - u.Y*v.X;
	}

	bool IsPointInTriangle(vec2f const & a, vec2f const & b, vec2f const & c, vec2f const & point)
	{
		return Determinant(b - a, point - a) > 0 && Determinant(c - b, point - b) > 0 && Determinant(a - c, point - c) > 0;
	}

	bool IsPointInOrOnTriangle(vec2f const & a, vec2f const & b, vec2f const & c, vec2f const & point)
	{
		return Determinant(b - a, point - a) >= 0 && Determinant(c - b, point - b) >= 0 && Determinant(a - c, point - c) >= 0;
	}


	double Determinant(vec2d const & u, vec2d const & v)
	{
		return u.X*v.Y - u.Y*v.X;
	}

	bool IsPointInTriangle(vec2d const & a, vec2d const & b, vec2d const & c, vec2d const & point)
	{
		return Determinant(b - a, point - a) > 0 && Determinant(c - b, point - b) > 0 && Determinant(a - c, point - c) > 0;
	}

	bool IsPointInOrOnTriangle(vec2d const & a, vec2d const & b, vec2d const & c, vec2d const & point)
	{
		return Determinant(b - a, point - a) >= 0 && Determinant(c - b, point - b) >= 0 && Determinant(a - c, point - c) >= 0;
	}


	template <typename T>
	vector<STriangle2D<T>> TriangulateEarClipping_Implementation(vector<vec2<T>> const & OriginalPoints)
	{
		vector<STriangle2D<T>> Return;
		vector<vec2<T>> Points = OriginalPoints;

		if (Points.size() >= 3)
		{
			bool TriangleFound = true;

			while (Points.size() != 0)
			{
				if (! TriangleFound)
					return Return;

				TriangleFound = false;

				for (int i(0); i < Points.size() - 2; i++)
				{
					if (! TriangleFound)
					{
						bool result = false;
						if (Determinant(Points[i + 1] - Points[i], Points[i + 2] - Points[i + 1]) < 0)
						{
							result = true;
							for (int j(0); j < OriginalPoints.size(); j++)
							{
								if (IsPointInTriangle(Points[i + 2], Points[i + 1], Points[i], OriginalPoints[j]))
								{
									result = false;
								}
							}
						}

						if (result)
						{
							TriangleFound = true;

							STriangle2D<T> tri;
							tri.A = Points[i];
							tri.B = Points[i + 1];
							tri.C = Points[i + 2];
							Return.push_back(tri);

							Points.erase(Points.begin() + i + 1);
						}
					}
				}
			}
		}

		return Return;
	}

	vector<STriangle2D<float>> TriangulateEarClipping(vector<vec2f> const & OriginalPoints)
	{
		return TriangulateEarClipping_Implementation(OriginalPoints);
	}

	vector<STriangle2D<double>> TriangulateEarClipping(vector<vec2d> const & OriginalPoints)
	{
		return TriangulateEarClipping_Implementation(OriginalPoints);
	}

}
