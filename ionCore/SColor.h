#ifndef _CABBAGE_CORE_SCOLOR_H_INCLUDED_
#define _CABBAGE_CORE_SCOLOR_H_INCLUDED_

#include "SVector3.h"

class SColor
{

public:

    float Red, Green, Blue, Alpha;

    SColor()
        : Red(0.7f), Green(0.7f), Blue(0.7f), Alpha(1.f)
    {}

	SColor(float red, float green, float blue)
        : Red(red), Green(green), Blue(blue), Alpha(1.f)
    {}

	static SColor const SColori(unsigned int const red, unsigned int const green, unsigned int const blue)
	{
		SColor c;
        c.Red=(red / 255.f);
		c.Green=(green / 255.f);
		c.Blue=(blue / 255.f);
		c.Alpha=(1.f);
		return c;
    }

	SColor(float red, float green, float blue, float alpha)
        : Red(red), Green(green), Blue(blue), Alpha(alpha)
    {}

	SColor(SVector3f const & vector)
		: Red(vector.X), Green(vector.Y), Blue(vector.Z), Alpha(1.f)
	{}

	float const operator[] (unsigned int i) const
	{
		switch (i)
		{
		default:
		case 0:
			return Red;
		case 1:
			return Green;
		case 2:
			return Blue;
		case 3:
			return Alpha;
		}
	}

	float & operator[] (unsigned int i)
	{
		switch (i)
		{
		default:
		case 0:
			return Red;
		case 1:
			return Green;
		case 2:
			return Blue;
		case 3:
			return Alpha;
		}
	}

	template <typename T>
	SColor operator * (T const s) const
	{
		return SColor(Red*s, Green*s, Blue*s, Alpha*s);
	}

	SColor operator * (SColor const & s) const
	{
		return SColor(Red * s.Red, Green * s.Green, Blue * s.Blue, Alpha * s.Alpha);
	}

	SColor operator + (SColor const & s) const
	{
		return SColor(Red + s.Red, Green + s.Green, Blue + s.Blue, Alpha + s.Alpha);
	}

	SColor & operator *= (SColor const & s)
	{
		Red *= s.Red;
		Green *= s.Green;
		Blue *= s.Blue;
		Alpha *= s.Alpha;
		return * this;
	}
	
	template <typename T>
	SColor & operator *= (T const s)
	{
		Red *= s;
		Green *= s;
		Blue *= s;
		Alpha *= s;
		return * this;
	}

	bool const operator == (SColor const & c)
	{
		return equals(Red, c.Red) && equals(Green, c.Green) && equals(Blue, c.Blue) && equals(Alpha, c.Alpha);
	}

};

#endif
