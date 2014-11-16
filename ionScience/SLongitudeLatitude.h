
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

	using SVectorBase<T, 2>::Values;
	using SVectorBase<T, 2>::reset;

	T & Longitude;
	T & Latitude;

	//! Default constructor
	SLongitudeLatitude()
		: Longitude(Values[0]), Latitude(Values[1])
	{
		reset();
	}

	//! Scalar constructor
	SLongitudeLatitude(T const in)
		: Longitude(Values[0]), Latitude(Values[1])
	{
		set(in);
	}

	//! Explicit constructor
	SLongitudeLatitude(T const lon, T const lat)
		: Longitude(Values[0]), Latitude(Values[1])
	{
		Values[0] = lon;
		Values[1] = lat;
	}

	//! Copy constructor
	SLongitudeLatitude(SLongitudeLatitude<T> const & vec)
		: Longitude(Values[0]), Latitude(Values[1])
	{
		set(vec);
	}

	//! Assignment operator
	SLongitudeLatitude<T> & operator = (SLongitudeLatitude<T> const & vec)
	{
		set(vec);

		return * this;
	}

	static T DMStoDecimal(T const Degrees, T const Minutes, T const Seconds, ECompassDirection const Direction = ECompassDirection::N)
	{
		return (Degrees + Minutes/60 + Seconds/3600) * (int) Direction;
	}

	static void DecimalToDMS(T const Decimal, T & Degrees, T & Minutes, T & Seconds)
	{
		T Remainder = Decimal;

		Degrees = floor(Remainder);
		Remainder -= Degrees;

		Remainder *= 60;
		Minutes = floor(Remainder);
		Remainder -= Minutes;

		Remainder *= 60;
		Seconds = Remainder;
	}

	static T DMStoDecimal(std::string const & String)
	{
		f64 Deg, Min, Sec;
		char Dir;
		ECompassDirection Direction;

		sscanf(String.c_str(), "%lf %lf %lf %c", & Deg, & Min, & Sec, & Dir);

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

		return DMStoDecimal(Deg, Min, Sec, Direction);
	}

	vec2f Vector() const
	{
		return vec2f(Longitude, Latitude);
	}

	class IProjectionSystem
	{

	public:

		virtual T DistanceBetween(SLongitudeLatitude const &, SLongitudeLatitude const &) = 0;
		virtual SVector2<T> OffsetBetween(SLongitudeLatitude const &, SLongitudeLatitude const &) = 0;

	};

	class CHaversineProjection : public IProjectionSystem
	{

	public:

		enum class EOffsetMode
		{
			Left,
			Right,
			Average
		};

		T DistanceBetween(SLongitudeLatitude const & Left, SLongitudeLatitude const & Right)
		{
			T EarthRadius = (T) 6378.137;
			T DeltaLat = DegreesToRadians(Right.Latitude - Left.Latitude);
			T DeltaLong = DegreesToRadians(Right.Longitude - Left.Longitude);
			T A =
				Sin(DeltaLat / 2) * Sin(DeltaLat / 2) +
				Cos(DegreesToRadians(Left.Latitude)) * Cos(DegreesToRadians(Right.Latitude)) * Sin(DeltaLong / 2) * Sin(DeltaLong / 2);
			T C = 2 * ArcTan(Sqrt(A), Sqrt(1 - A));
			T Distance = EarthRadius * C;

			return Distance * 1000;
		}

		SVector2<T> OffsetBetween(SLongitudeLatitude const & A, SLongitudeLatitude const & B)
		{
			SVector2<T> Offset;
			SLongitudeLatitude Left, Right;

			Left.Longitude = A.Longitude;
			Right.Longitude = B.Longitude;
			switch (OffsetMode)
			{
			default:
			case EOffsetMode::Average:
				Left.Latitude = Right.Latitude = (A.Latitude + B.Latitude) / 2;
				break;
			case EOffsetMode::Left:
				Left.Latitude = Right.Latitude = A.Latitude;
				break;
			case EOffsetMode::Right:
				Left.Latitude = Right.Latitude = B.Latitude;
				break;
			}
			Offset.X = (Left.Longitude < Right.Longitude ? 1 : -1) * DistanceBetween(Left, Right);

			Left.Latitude = A.Latitude;
			Right.Latitude = B.Latitude;
			switch (OffsetMode)
			{
			default:
			case EOffsetMode::Average:
				Left.Longitude = Right.Longitude = (A.Longitude + B.Longitude) / 2;
				break;
			case EOffsetMode::Left:
				Left.Longitude = Right.Longitude = A.Longitude;
				break;
			case EOffsetMode::Right:
				Left.Longitude = Right.Longitude = B.Longitude;
				break;
			}
			Offset.Y = (Left.Latitude < Right.Latitude ? 1 : -1) * DistanceBetween(Left, Right);

			return Offset;
		}

		CHaversineProjection()
			: OffsetMode(EOffsetMode::Average)
		{}

		CHaversineProjection(EOffsetMode const offsetMode)
			: OffsetMode(OffsetMode)
		{}

		EOffsetMode OffsetMode;

	};

	class CVincentyProjection : public CHaversineProjection
	{

	public:

		T DistanceBetween(SLongitudeLatitude const & Left, SLongitudeLatitude const & Right)
		{
			T const lon1 = DegreesToRadians(Left.Longitude), lat1 = DegreesToRadians(Left.Latitude);
			T const lon2 = DegreesToRadians(Right.Longitude), lat2 = DegreesToRadians(Right.Latitude);

			T const a = (T) 6378137, b = (T) 6356752.314245,  f = (T) (1 / 298.257223563);  // WGS-84 ellipsoid params
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
				std::cerr << "Failed to converge in Vincenty Long/Lat conversion." << std::endl;
				return std::numeric_limits<T>::max();  // formula failed to converge
			}

			T uSq = cosSqAlpha * (a*a - b*b) / (b*b);
			T A = 1 + uSq/16384*(4096+uSq*(-768+uSq*(320-175*uSq)));
			T B = uSq/1024 * (256+uSq*(-128+uSq*(74-47*uSq)));
			T deltaSigma = B*sinSigma*(cos2SigmaM+B/4*(cosSigma*(-1+2*cos2SigmaM*cos2SigmaM) - B/6*cos2SigmaM*(-3+4*sinSigma*sinSigma)*(-3+4*cos2SigmaM*cos2SigmaM)));
			T s = b*A*(sigma-deltaSigma);

			return s;
		}

		CVincentyProjection()
		{}

		// Doesn't compile on g++ 4.4.7 for some reason
		// CVincentyProjection(CHaversineProjection::EOffsetMode const offsetMode)
		// 	: CHaversineProjection(OffsetMode)
		// {}

	};

	class CEquirectangularProjection : public IProjectionSystem
	{

	public:

		T DistanceBetween(SLongitudeLatitude const & Left, SLongitudeLatitude const & Right)
		{
			CHaversineProjection Haversine;
			SLongitudeLatitude const Center((Left.Longitude + Right.Longitude) / 2, PhiStandard);
			SVector2<T> const UnitLength = Haversine.OffsetBetween(Center - 0.5, Center + 0.5);

			SVector2<T> LeftProjected(Left.Longitude * Cos(PhiStandard), Left.Latitude);
			SVector2<T> RightProjected(Right.Longitude * Cos(PhiStandard), Right.Latitude);

			LeftProjected *= UnitLength;
			RightProjected *= UnitLength;

			return LeftProjected.GetDistanceFrom(RightProjected);
		}

		virtual SVector2<T> OffsetBetween(SLongitudeLatitude const & Left, SLongitudeLatitude const & Right)
		{
			CHaversineProjection Haversine;
			SLongitudeLatitude const Center((Left.Longitude + Right.Longitude) / 2, PhiStandard);
			SVector2<T> const UnitLength = Haversine.OffsetBetween(Center - 0.5, Center + 0.5);

			SVector2<T> LeftProjected(Left.Longitude * Cos(PhiStandard), Left.Latitude);
			SVector2<T> RightProjected(Right.Longitude * Cos(PhiStandard), Right.Latitude);

			LeftProjected *= UnitLength;
			RightProjected *= UnitLength;

			return RightProjected - LeftProjected;
		}

		CEquirectangularProjection(T const phiStandard)
			: PhiStandard(phiStandard)
		{}

		T PhiStandard;

	};

	T DistanceTo(SLongitudeLatitude const & Other, sharedPtr<IProjectionSystem> Projection = sharedNew(new CHaversineProjection())) const
	{
		return Projection->DistanceBetween(* this, Other);
	}

	SVector2<T> OffsetTo(SLongitudeLatitude const & Other, sharedPtr<IProjectionSystem> Projection = sharedNew(new CHaversineProjection())) const
	{
		return Projection->OffsetBetween(* this, Other);
	}

};


typedef SLongitudeLatitude<f32> SLongitudeLatitudef;
typedef SLongitudeLatitude<f64> SLongitudeLatituded;

typedef SLongitudeLatitudef longlatf;
typedef SLongitudeLatituded longlatd;
