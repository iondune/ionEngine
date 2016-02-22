
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

	}
}