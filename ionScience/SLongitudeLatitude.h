
#pragma once

#include <ionMath.h>


enum class ECompassDirection
{
	N = 1, E = 1,
	S = -1, W = -1
};

template <typename T>
struct SLongitudeLatitude : public SVector<T, 2, SLongitudeLatitude<T> >
{

	T & Longitude;
	T & Latitude;

	//! Default constructor
	ION_FUNC_DEF SLongitudeLatitude()
		: Longitude(Values[0]), Latitude(Values[1])
	{
		reset();
	}
	
	//! Scalar constructor
	ION_FUNC_DEF SLongitudeLatitude(T const in)
		: Longitude(Values[0]), Latitude(Values[1])
	{
		set(in);
	}

	//! Explicit constructor
	ION_FUNC_DEF SLongitudeLatitude(T const x, T const y)
		: Longitude(Values[0]), Latitude(Values[1])
	{
		Values[0] = x;
		Values[1] = y;
	}

	//! Copy constructor
	ION_FUNC_DEF SLongitudeLatitude(SLongitudeLatitude<T> const & vec)
		: Longitude(Values[0]), Latitude(Values[1])
	{
		set(vec);
	}

	//! Assignment operator
	ION_FUNC_DEF SLongitudeLatitude<T> & operator = (SLongitudeLatitude<T> const & vec)
	{
		set(vec);

		return * this;
	}

	ION_FUNC_DEF static T DMStoDecimal(T const Degrees, T const Minutes, T const Seconds, ECompassDirection const Direction = ECompassDirection::N)
	{
		return (Degrees + Minutes/60 + Seconds/3600) * (int) Direction;
	}

	ION_FUNC_DEF static T DMStoDecimal(std::string const & String)
	{
		f64 Deg, Min, Sec;
		char Dir, Dummy;
		ECompassDirection Direction;

		sscanf(String.c_str(), "%lf %c %lf %c %lf %c %c", & Deg, & Dummy, & Min, & Dummy, & Sec, & Dummy, & Dir);
	
		switch (tolower(Dir))
		{
		default:
		case 'N':
			Direction = ECompassDirection::N;
			break;
		case 'E':
			Direction = ECompassDirection::E;
			break;
		case 'S':
			Direction = ECompassDirection::S;
			break;
		case 'W':
			Direction = ECompassDirection::W;
			break;
		}

		return LongLatDecimalDegrees(Deg, Min, Sec, Direction);
	}

	ION_FUNC_DEF vec2f Vector() const
	{
		return vec2f(Longitude, Latitude);
	}

	ION_FUNC_DEF T DistanceTo(SLongitudeLatitude const & Other) const
	{
		T EarthRadius = (T) 6378.137;
		T DeltaLat = DegreesToRadians(Other.Latitude - Latitude);
		T DeltaLong = DegreesToRadians(Other.Longitude - Longitude);
		T A = 
			Sin(DeltaLat / 2) * Sin(DeltaLat / 2) +
			Cos(DegreesToRadians(Latitude)) * Cos(DegreesToRadians(Other.Latitude)) * Sin(DeltaLong / 2) * Sin(DeltaLong / 2);
		T C = 2 * ArcTan(Sqrt(A), Sqrt(1 - A));
		T Distance = EarthRadius * C;

		return Distance * 1000;
	}

	ION_FUNC_DEF T VincentyDistanceTo(SLongitudeLatitude const & Other) const
	{
		T const lon1 = DegreesToRadians(Longitude), lat1 = DegreesToRadians(Latitude);
		T const lon2 = DegreesToRadians(Other.Longitude), lat2 = DegreesToRadians(Other.Latitude);
		//T const a = (T) 6378137, b = (T) 6356752.314245,  f = (T) (1 / 298.257223563);  // WGS-84 ellipsoid params
		T const a = (T) 6378388, b = (T) 6356911.946,  f = (T) (1 / 297.0);  // WGS-84 ellipsoid params
		T const L = lon2 - lon1;
		T const U1 = ArcTan((1-f) * Tan(lat1));
		T const U2 = ArcTan((1-f) * Tan(lat2));
		T const sinU1 = Sin(U1), cosU1 = Cos(U1);
		T const sinU2 = Sin(U2), cosU2 = Cos(U2);

		T lambda = L, lambdaP, iterLimit = 100;
		T cosSqAlpha, sinSigma, cos2SigmaM, cosSigma, sigma;
		do {
			T sinLambda = Sin(lambda), cosLambda = Cos(lambda);
			sinSigma = Sqrt((cosU2*sinLambda) * (cosU2*sinLambda) + 
				(cosU1*sinU2-sinU1*cosU2*cosLambda) * (cosU1*sinU2-sinU1*cosU2*cosLambda));
			if (sinSigma==0)
				return 0; // co-incident points
			cosSigma = sinU1*sinU2 + cosU1*cosU2*cosLambda;
			sigma = ArcTan(sinSigma, cosSigma);
			T sinAlpha = cosU1 * cosU2 * sinLambda / sinSigma;
			cosSqAlpha = 1 - sinAlpha*sinAlpha;
			cos2SigmaM = cosSigma - 2*sinU1*sinU2/cosSqAlpha;
			if (IsNaN(cos2SigmaM))
				cos2SigmaM = 0;  // equatorial line: cosSqAlpha=0 (§6)
			T C = f/16*cosSqAlpha*(4+f*(4-3*cosSqAlpha));
			lambdaP = lambda;
			lambda = L + (1-C) * f * sinAlpha * (sigma + C*sinSigma*(cos2SigmaM+C*cosSigma*(-1+2*cos2SigmaM*cos2SigmaM)));
		}
		while (Abs(lambda-lambdaP) > 1e-12 && --iterLimit>0);

		if (iterLimit==0)
		{
			std::cerr << "Failed to converge in Long/Lat conversion." << std::endl;
			return std::numeric_limits<T>::max();  // formula failed to converge
		}

		T uSq = cosSqAlpha * (a*a - b*b) / (b*b);
		T A = 1 + uSq/16384*(4096+uSq*(-768+uSq*(320-175*uSq)));
		T B = uSq/1024 * (256+uSq*(-128+uSq*(74-47*uSq)));
		T deltaSigma = B*sinSigma*(cos2SigmaM+B/4*(cosSigma*(-1+2*cos2SigmaM*cos2SigmaM) - B/6*cos2SigmaM*(-3+4*sinSigma*sinSigma)*(-3+4*cos2SigmaM*cos2SigmaM)));
		T s = b*A*(sigma-deltaSigma);

		return s;
	}

	enum class EOffsetMode
	{
		Left,
		Right,
		Average
	};

	ION_FUNC_DEF SVector2<T> OffsetTo(SLongitudeLatitude const & Other, EOffsetMode const Mode = EOffsetMode::Average, bool const Vincenty = false) const
	{
		SVector2<T> Offset;
		SLongitudeLatitude Left, Right;

		Left.Longitude = Longitude;
		Right.Longitude = Other.Longitude;
		switch (Mode)
		{
		default:
		case EOffsetMode::Average:
			Left.Latitude = Right.Latitude = (Latitude + Other.Latitude) / 2;
			break;
		case EOffsetMode::Left:
			Left.Latitude = Right.Latitude = Latitude;
			break;
		case EOffsetMode::Right:
			Left.Latitude = Right.Latitude = Other.Latitude;
			break;
		}
		if (Vincenty)
			Offset.X = (Left.Longitude < Right.Longitude ? 1 : -1) * Left.VincentyDistanceTo(Right);
		else
			Offset.X = (Left.Longitude < Right.Longitude ? 1 : -1) * Left.DistanceTo(Right);

		Left.Latitude = Latitude;
		Right.Latitude = Other.Latitude;
		switch (Mode)
		{
		default:
		case EOffsetMode::Average:
			Left.Longitude = Right.Longitude = (Longitude + Other.Longitude) / 2;
			break;
		case EOffsetMode::Left:
			Left.Longitude = Right.Longitude = Longitude;
			break;
		case EOffsetMode::Right:
			Left.Longitude = Right.Longitude = Other.Longitude;
			break;
		}
		if (Vincenty)
			Offset.Y = (Left.Latitude < Right.Latitude ? 1 : -1) * Left.VincentyDistanceTo(Right);
		else
			Offset.Y = (Left.Latitude < Right.Latitude ? 1 : -1) * Left.DistanceTo(Right);

		return Offset;
	}

};


typedef SLongitudeLatitude<f32> SLongitudeLatitudef;
typedef SLongitudeLatitude<f64> SLongitudeLatituded;

typedef SLongitudeLatitudef longlatf;
typedef SLongitudeLatituded longlatd;
