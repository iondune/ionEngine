
#pragma once

#include <ionCore.h>
#include <ionMath.h>


namespace ion
{
	namespace Animation
	{

		struct S3DSplineNode
		{
			vec3f Position;
			vec3f Normal = vec3f(0, 1, 0);
			vec3f Tangent = vec3f(1, 0, 0);

			S3DSplineNode operator + (S3DSplineNode const & v) const
			{
				S3DSplineNode copy;
				copy.Position = Position + v.Position;
				copy.Normal = Normal + v.Normal;
				copy.Tangent = Tangent + v.Tangent;

				return copy;
			}

			S3DSplineNode operator - (S3DSplineNode const & v) const
			{
				S3DSplineNode copy;
				copy.Position = Position - v.Position;
				copy.Normal = Normal - v.Normal;
				copy.Tangent = Tangent - v.Tangent;

				return copy;
			}

			S3DSplineNode operator * (float const & s) const
			{
				S3DSplineNode copy;
				copy.Position = Position * s;
				copy.Normal = Normal * s;
				copy.Tangent = Tangent * s;

				return copy;
			}

			S3DSplineNode operator / (float const & s) const
			{
				S3DSplineNode copy;
				copy.Position = Position / s;
				copy.Normal = Normal / s;
				copy.Tangent = Tangent / s;

				return copy;
			}

			S3DSplineNode operator + (vec3f const & v) const
			{
				S3DSplineNode copy = *this;
				copy.Position = Position + v;

				return copy;
			}

			S3DSplineNode operator - (vec3f const & v) const
			{
				S3DSplineNode copy = *this;
				copy.Position = Position - v;

				return copy;
			}

			float GetLength() const
			{
				return Position.Length();
			}

		};

	}
}
