
#pragma once

#include <ionCore.h>
#include <ionMath.h>


struct SPathNode
{
	vec3f Position;
	vec3f Normal;


	SPathNode()
		: Normal(0, 1, 0)
	{}

	SPathNode(float const x, float const y, float const z, float const i = 0, float const j = 1, float const k = 0)
		: Position(x, y, z), Normal(i, j, k)
	{}

	SPathNode operator + (SPathNode const & v) const
	{
		SPathNode copy;
		copy.Position = Position + v.Position;
		copy.Normal = Normal + v.Normal;

		return copy;
	}

	SPathNode operator - (SPathNode const & v) const
	{
		SPathNode copy;
		copy.Position = Position - v.Position;
		copy.Normal = Normal - v.Normal;

		return copy;
	}

	SPathNode operator * (float const & s) const
	{
		SPathNode copy;
		copy.Position = Position * s;
		copy.Normal = Normal * s;

		return copy;
	}

	SPathNode operator / (float const & s) const
	{
		SPathNode copy;
		copy.Position = Position / s;
		copy.Normal = Normal / s;

		return copy;
	}

	float const length() const
	{
		return Position.Length();
	}

};
