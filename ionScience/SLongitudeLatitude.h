
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
		T EarthRadius = 6371;
		T DeltaLat = DegreesToRadians(Other.Latitude - Latitude);
		T DeltaLong = DegreesToRadians(Other.Longitude - Longitude);
		T A = 
			Sin(DeltaLat / 2) * Sin(DeltaLat / 2) +
			Cos(DegreesToRadians(Latitude)) * Cos(DegreesToRadians(Other.Latitude)) * Sin(DeltaLong / 2) * Sin(DeltaLong / 2);
		T C = 2 * ArcTan(Sqrt(A), Sqrt(1 - A));
		T Distance = EarthRadius * C;

		return Distance * 1000;
	}

	enum class EOffsetMode
	{
		Left,
		Right,
		Average
	};

	ION_FUNC_DEF SVector2<T> OffsetTo(SLongitudeLatitude const & Other, EOffsetMode const Mode = EOffsetMode::Average) const
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
		Offset.Y = (Left.Latitude < Right.Latitude ? 1 : -1) * Left.DistanceTo(Right);

		return Offset;
	}

};


typedef SLongitudeLatitude<f32> SLongitudeLatitudef;
typedef SLongitudeLatitude<f64> SLongitudeLatituded;

typedef SLongitudeLatitudef longlatf;
typedef SLongitudeLatituded longlatd;
