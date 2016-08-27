
#include "EarClipping.h"


namespace ion
{

	float Determinant(vec2f const & u, vec3f const & v)
	{
		return u.X*v.Y - u.Y*v.X;
	}

	bool IsPointInTriangle(vec2f const & a, vec2f const & b, vec2f const & c, vec2f const & point)
	{
		if (Determinant(b - a, point - a) > 0 && Determinant(c - b, point - b) > 0 && Determinant(a - c, point - c) > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	vector<STriangle2D> TriangulateEarClipping(vector<vec2f> const & OriginalPoints)
	{
		vector<STriangle2D> Return;
		vector<vec2f> Points = OriginalPoints;

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

							STriangle2D tri;
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

}
