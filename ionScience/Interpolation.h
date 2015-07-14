
#pragma once

template <typename T>
T LinearInterpolate(T p1, T p2, T x)
{
	return p1*(1 - x) + p2*x;
}

template <typename T>
T LinearInterpolate(T p[2], T x)
{
	return p[0]*(1 - x) + p[1]*x;
}

template <typename T>
T BilinearInterpolate(T p[2][2], T x, T y)
{
	T arr[2];
	arr[0] = LinearInterpolate(p[0], y);
	arr[1] = LinearInterpolate(p[1], y);
	return LinearInterpolate(arr, x);
}

template <typename T>
T TrilinearInterpolate(T p[2][2][2], T x, T y, T z)
{
	T arr[2];
	arr[0] = BilinearInterpolate(p[0], y, z);
	arr[1] = BilinearInterpolate(p[1], y, z);
	return LinearInterpolate(arr, x);
}

template <typename T>
T CubicInterpolate(T p[4], T x)
{
	return p[1] + (T) 0.5 * x*(p[2] - p[0] + x*(2*p[0] - 5*p[1] + 4*p[2] - p[3] + x*(3*(p[1] - p[2]) + p[3] - p[0])));
}

template <typename T>
T BicubicInterpolate(T p[4][4], T x, T y)
{
	T arr[4];
	arr[0] = CubicInterpolate(p[0], y);
	arr[1] = CubicInterpolate(p[1], y);
	arr[2] = CubicInterpolate(p[2], y);
	arr[3] = CubicInterpolate(p[3], y);
	return CubicInterpolate(arr, x);
}

template <typename T>
T TricubicInterpolate(T p[4][4][4], T x, T y, T z)
{
	T arr[4];
	arr[0] = BicubicInterpolate(p[0], y, z);
	arr[1] = BicubicInterpolate(p[1], y, z);
	arr[2] = BicubicInterpolate(p[2], y, z);
	arr[3] = BicubicInterpolate(p[3], y, z);
	return CubicInterpolate(arr, x);
}

template <typename T>
T Gaussian(T x, T sigma)
{
	return pow(Constants32::e, - Sq(x) / (2 * Sq(sigma))) / sqrt(2 * Constants32::Pi * Sq(sigma));
}
