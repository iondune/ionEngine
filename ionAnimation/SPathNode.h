
#pragma once

#include <ionCore.h>
#include <ionMath.h>


namespace ion
{
	namespace Animation
	{

		struct S3DPathNode
		{
			vec3f Position;
			vec3f Normal = vec3f(0, 1, 0);
			vec3f Tangent = vec3f(1, 0, 0);

			S3DPathNode operator + (S3DPathNode const & v) const
			{
				S3DPathNode copy;
				copy.Position = Position + v.Position;
				copy.Normal = Normal + v.Normal;
				copy.Tangent = Tangent + v.Tangent;

				return copy;
			}

			S3DPathNode operator - (S3DPathNode const & v) const
			{
				S3DPathNode copy;
				copy.Position = Position - v.Position;
				copy.Normal = Normal - v.Normal;
				copy.Tangent = Tangent - v.Tangent;

				return copy;
			}

			S3DPathNode operator * (float const & s) const
			{
				S3DPathNode copy;
				copy.Position = Position * s;
				copy.Normal = Normal * s;
				copy.Tangent = Tangent * s;

				return copy;
			}

			S3DPathNode operator / (float const & s) const
			{
				S3DPathNode copy;
				copy.Position = Position / s;
				copy.Normal = Normal / s;
				copy.Tangent = Tangent / s;

				return copy;
			}

			S3DPathNode operator + (vec3f const & v) const
			{
				S3DPathNode copy = *this;
				copy.Position = Position + v;

				return copy;
			}

			S3DPathNode operator - (vec3f const & v) const
			{
				S3DPathNode copy = *this;
				copy.Position = Position - v;

				return copy;
			}

			float const GetLength() const
			{
				return Position.Length();
			}

		};

	}
}
