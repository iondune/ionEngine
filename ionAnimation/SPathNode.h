
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


			S3DPathNode()
			{}

			S3DPathNode(float const x, float const y, float const z, float const i = 0, float const j = 1, float const k = 0)
				: Position(x, y, z), Normal(i, j, k)
			{}

			S3DPathNode operator + (S3DPathNode const & v) const
			{
				S3DPathNode copy;
				copy.Position = Position + v.Position;
				copy.Normal = Normal + v.Normal;

				return copy;
			}

			S3DPathNode operator - (S3DPathNode const & v) const
			{
				S3DPathNode copy;
				copy.Position = Position - v.Position;
				copy.Normal = Normal - v.Normal;

				return copy;
			}

			S3DPathNode operator * (float const & s) const
			{
				S3DPathNode copy;
				copy.Position = Position * s;
				copy.Normal = Normal * s;

				return copy;
			}

			S3DPathNode operator / (float const & s) const
			{
				S3DPathNode copy;
				copy.Position = Position / s;
				copy.Normal = Normal / s;

				return copy;
			}

			float const GetLength() const
			{
				return Position.Length();
			}

		};

	}
}
