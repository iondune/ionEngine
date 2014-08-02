
#pragma once

#include <ionCore.h>


class IFont
{

public:

	static IFont * init(const char * fname, unsigned int h);

	virtual ~IFont()
	{}

	//virtual void measure(int * width, int * height, char const * fmt, ...) = 0;

	virtual void print(float x, float y, const char *fmt, ...) = 0;

protected:

	IFont()
	{}

};
