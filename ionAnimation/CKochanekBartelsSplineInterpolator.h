
#pragma once

#include "ISplineInterpolator.h"


namespace ion
{
	namespace Animation
	{

		template <typename T>
		class CKochanekBartelsSplineInterpolator : public ISplineInterpolator<T>
		{

		protected:

			float Tension = 0;
			float Bias = 0;

		public:

			virtual T Interpolate(ISpline<T> const & Path, int const Index, float const Mu);

			void SetBias(float const bias) { Bias = bias; }
			void SetTension(float const tension) { Tension = tension; }

			float GetBias() const { return Bias; }
			float GetTension() const { return Tension; }

		};

		template <typename T>
		T CKochanekBartelsSplineInterpolator<T>::Interpolate(ISpline<T> const & Path, int const Index, float const Mu)
		{
			T const y0 = Path.GetNode(Index - 1);
			T const y1 = Path.GetNode(Index + 0);
			T const y2 = Path.GetNode(Index + 1);
			T const y3 = Path.GetNode(Index + 2);

			float const mu = Mu;
			float const mu2 = Sq(mu);
			float const mu3 = mu2 * mu;

			T m0 = (y1 - y0)*(1 + Bias)*(1 - Tension) / 2;
			m0 = m0 + (y2 - y1)*(1 - Bias)*(1 - Tension) / 2;
			T m1 = (y2 - y1)*(1 + Bias)*(1 - Tension) / 2;
			m1 = m1 + (y3 - y2)*(1 - Bias)*(1 - Tension) / 2;

			float const a0 = 2.f*mu3 - 3 * mu2 + 1;
			float const a1 = mu3 - 2 * mu2 + mu;
			float const a2 = mu3 - mu2;
			float const a3 = -2.f*mu3 + 3 * mu2;

			return y1*a0 + m0*a1 + m1*a2 + y2*a3;
		}

	}
}
