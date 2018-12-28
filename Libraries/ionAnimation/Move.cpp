
#include "Move.h"



namespace ion
{
	namespace Animation
	{

		float Move::Linear(float From, float const To, float const Elapsed, float const Speed, float const Clamp)
		{
			if (From > To + Clamp)
			{
				From -= Speed * Elapsed;
				if (From < To + Clamp)
				{
					From = To;
				}
			}
			if (From < To - Clamp)
			{
				From += Speed * Elapsed;
				if (From > To - Clamp)
				{
					From = To;
				}
			}

			return From;
		}

		vec3f Move::Linear(vec3f From, vec3f const & To, float const Elapsed, float const Speed, float const Clamp)
		{
			vec3f const DirectionVector = To - From;
			float const DistanceToGo = DirectionVector.Length();

			if (DistanceToGo < Clamp)
			{
				From = To;
			}
			else
			{
				float const DistanceCanGo = Speed * Elapsed;

				if (DistanceCanGo > DistanceToGo)
				{
					From = To;
				}
				else
				{
					From += DirectionVector.GetNormalized() * DistanceCanGo;
				}
			}

			return From;
		}

		vec3f Move::Quadratic(vec3f From, vec3f const & To, float const Elapsed, float const Speed, float const Clamp)
		{
			vec3f const DirectionVector = To - From;
			float const DistanceToGo = DirectionVector.Length();

			if (DistanceToGo < Clamp)
			{
				From = To;
			}
			else
			{
				float const DistanceCanGo = Speed * Elapsed * DistanceToGo;

				if (DistanceCanGo > DistanceToGo)
				{
					From = To;
				}
				else
				{
					From += DirectionVector.GetNormalized() * DistanceCanGo;
				}
			}

			return From;
		}

		float Move::Quadratic(float From, float const To, float const Elapsed, float const Speed, float const Clamp)
		{
			float const DistanceCanGo = Speed * Elapsed * Abs(To - From);

			if (From > To + Clamp)
			{
				From -= DistanceCanGo;
				if (From < To + Clamp)
				{
					From = To;
				}
			}
			if (From < To - Clamp)
			{
				From += DistanceCanGo;
				if (From > To - Clamp)
				{
					From = To;
				}
			}

			return From;
		}

		vec3f Move::Cubic(vec3f From, vec3f const & To, float const Elapsed, float const Speed, float const Clamp)
		{
			vec3f const DirectionVector = To - From;
			float const DistanceToGo = DirectionVector.Length();

			if (DistanceToGo < Clamp)
			{
				From = To;
			}
			else
			{
				float const DistanceCanGo = Speed * Elapsed * DistanceToGo * DistanceToGo;

				if (DistanceCanGo > DistanceToGo)
				{
					From = To;
				}
				else
				{
					From += DirectionVector.GetNormalized() * DistanceCanGo;
				}
			}

			return From;
		}

	}
}