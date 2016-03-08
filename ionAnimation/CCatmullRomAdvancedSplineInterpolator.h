
#pragma once

#include "ISplineInterpolator.h"


namespace ion
{
	namespace Animation
	{

		template <typename T>
		class CCatmullRomAdvancedSplineInterpolator : public ISplineInterpolator<T>
		{

		public:

			enum EMode
			{
				Uniform = 0,
				Centripetal = 1,
				Chordal = 2
			};

			EMode Mode;

			virtual T Interpolate(ISpline<T> const & Path, int const Index, float const Mu);

		};

		template <typename T>
		T CCatmullRomAdvancedSplineInterpolator<T>::Interpolate(ISpline<T> const & Path, int const Index, float const Mu)
		{
			// Uses notation from the Centripetal Catmull-Rom Spline article on Wikipedia.org:
			// https://en.wikipedia.org/wiki/Centripetal_Catmull%E2%80%93Rom_spline

			T const P0 = Path.GetNode(Index - 1);
			T const P1 = Path.GetNode(Index + 0);
			T const P2 = Path.GetNode(Index + 1);
			T const P3 = Path.GetNode(Index + 2);

			float Alpha = 0;
			if (Mode == EMode::Uniform)
				Alpha = 0;
			else if (Mode == EMode::Centripetal)
				Alpha = 0.5f;
			else if (Mode == EMode::Chordal)
				Alpha = 1;

			float const t0 = 0;
			float const t1 = pow((P1 - P0).GetLength(), Alpha) + t0;
			float const t2 = pow((P2 - P1).GetLength(), Alpha) + t1;
			float const t3 = pow((P3 - P2).GetLength(), Alpha) + t2;

			float const t = Mu * (t2 - t1) + t1;

			T const A1 = P0 * ((t1 - t) / (t1 - t0)) + P1 * ((t - t0) / (t1 - t0));
			T const A2 = P1 * ((t2 - t) / (t2 - t1)) + P2 * ((t - t1) / (t2 - t1));
			T const A3 = P2 * ((t3 - t) / (t3 - t2)) + P3 * ((t - t2) / (t3 - t2));

			T const B1 = A1 * ((t2 - t) / (t2 - t0)) + A2 * ((t - t0) / (t2 - t0));
			T const B2 = A2 * ((t3 - t) / (t3 - t1)) + A3 * ((t - t1) / (t3 - t1));

			return B1 * ((t2 - t) / (t2 - t1)) + B2 * ((t - t1) / (t2 - t1));
		}

	}
}
