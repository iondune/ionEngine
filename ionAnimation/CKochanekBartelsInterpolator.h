
#pragma once

#include "IInterpolator.h"


namespace ion
{
	namespace Animation
	{

		template <typename T>
		class CKochanekBartelsInterpolator : public IInterpolator<T>
		{

		protected:

			float Tension, Bias;

		public:

			CKochanekBartelsInterpolator();

			virtual T const Interpolate(IPath<T> const & Path, int const Index, float const Mu);

			void SetBias(float const bias) { Bias = bias; }
			void SetTension(float const tension) { Tension = tension; }

			float GetBias() const { return Bias; }
			float GetTension() const { return Tension; }

		};

		template <typename T>
		CKochanekBartelsInterpolator<T>::CKochanekBartelsInterpolator()
			: Tension(0.f), Bias(0.f)
		{}

		template <typename T>
		T const CKochanekBartelsInterpolator<T>::Interpolate(IPath<T> const & Path, s32 const Index, float const Mu)
		{
			T const y0 = Path.GetNode(Index - 1);
			T const y1 = Path.GetNode(Index + 0);
			T const y2 = Path.GetNode(Index + 1);
			T const y3 = Path.GetNode(Index + 2);

			f32 const mu = Mu;
			f32 const mu2 = Sq(mu);
			f32 const mu3 = mu2 * mu;

			T m0 = (y1 - y0)*(1 + Bias)*(1 - Tension) / 2;
			m0 = m0 + (y2 - y1)*(1 - Bias)*(1 - Tension) / 2;
			T m1 = (y2 - y1)*(1 + Bias)*(1 - Tension) / 2;
			m1 = m1 + (y3 - y2)*(1 - Bias)*(1 - Tension) / 2;

			f32 const a0 = 2.f*mu3 - 3 * mu2 + 1;
			f32 const a1 = mu3 - 2 * mu2 + mu;
			f32 const a2 = mu3 - mu2;
			f32 const a3 = -2.f*mu3 + 3 * mu2;

			return y1*a0 + m0*a1 + m1*a2 + y2*a3;
		}

	}
}
