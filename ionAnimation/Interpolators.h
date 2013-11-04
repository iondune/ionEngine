
#pragma once

#include "IInterpolator.h"


////////////
// Linear //
////////////

template <typename T>
class CLinearInterpolator : public IInterpolator<T>
{

public:

	virtual T const interpolate(IPath<T> const & Path, s32 const Index, float const Mu);

};

template <typename T>
T const CLinearInterpolator<T>::interpolate(IPath<T> const & Path, s32 const Index, float const Mu)
{
	return Path.getNode(Index) * (1.f - Mu) + Path.getNode(Index + 1) * Mu;
}


/////////////////
// Catmull-Rom //
/////////////////

template <typename T>
class CCatmullRomInterpolator : public IInterpolator<T>
{

public:

	virtual T const interpolate(IPath<T> const & Path, s32 const Index, float const Mu);

};

template <typename T>
T const CCatmullRomInterpolator<T>::interpolate(IPath<T> const & Path, s32 const Index, float const Mu)
{
	T const P0 = Path.getNode(Index - 1);
	T const P1 = Path.getNode(Index + 0);
	T const P2 = Path.getNode(Index + 1);
	T const P3 = Path.getNode(Index + 2);

	float const t = Mu;
	float const t2 = Sq(t);
	float const t3 = t2*t;

	return ((P1 * 2.0) + (P0*-1.0 + P2) * t + (P0*2.0 - P1*5.0 + P2*4.0 - P3) * t2 + (P0*-1.0 + P1*3.0 - P2*3.0 + P3) * t3) * 0.5;
}

////////////////////
// Hermite Spline //
////////////////////

template <typename T>
class CHermiteInterpolator : public IInterpolator<T>
{

protected:

	f32 Tension, Bias;

public:

	CHermiteInterpolator();

	virtual T const interpolate(IPath<T> const & Path, s32 const Index, float const Mu);

	f32 const setBias(f32 const bias) { return Bias = bias; }
	f32 const setTension(f32 const tension) { return Tension = tension; }

	f32 const getBias(f32 const bias) const { return Bias; }
	f32 const getTension(f32 const tension) const { return Tension; }

};

template <typename T>
CHermiteInterpolator<T>::CHermiteInterpolator()
	: Tension(0.f), Bias(0.f)
{}

template <typename T>
T const CHermiteInterpolator<T>::interpolate(IPath<T> const & Path, s32 const Index, float const Mu)
{
	T const y0 = Path.getNode(Index - 1);
	T const y1 = Path.getNode(Index + 0);
	T const y2 = Path.getNode(Index + 1);
	T const y3 = Path.getNode(Index + 2);

	f32 const mu = Mu;
	f32 const mu2 = Sq(mu);
	f32 const mu3 = mu2 * mu;

	T m0 = (y1-y0)*(1+Bias)*(1-Tension)/2;
	m0 = m0 + (y2-y1)*(1-Bias)*(1-Tension)/2;
	T m1 = (y2-y1)*(1+Bias)*(1-Tension)/2;
	m1 = m1 + (y3-y2)*(1-Bias)*(1-Tension)/2;

	f32 const a0 = 2.f*mu3 - 3*mu2 + 1;
	f32 const a1 = mu3 - 2*mu2 + mu;
	f32 const a2 = mu3 - mu2;
	f32 const a3 = -2.f*mu3 + 3*mu2;

	return y1*a0 + m0*a1 + m1*a2 + y2*a3;
}
