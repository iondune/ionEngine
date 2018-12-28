
#include "CSpline.h"


namespace ion
{
	namespace Animation
	{

		int IntermediateToIndex(float const Mu)
		{
			return static_cast<int>(floor(Mu) + RoundingError32);
		}

	}
}
