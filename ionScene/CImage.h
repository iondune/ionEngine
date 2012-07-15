#ifndef _CABBAGE_SCENE_CIMAGE_H_INCLUDED_
#define _CABBAGE_SCENE_CIMAGE_H_INCLUDED_

#include <string>

#ifdef __unix__
#include<GL/gl.h>
#endif

#ifdef _WIN32
#include <GL\glew.h>
#endif

#include "SVector2.h"
#include <SColor.h>

class CImage
{

	friend class CImageLoader;

	unsigned char * ImageData;
	int Width;
	int Height;

	bool Alpha;


public:

	CImage(unsigned char * imageData, int width, int height, bool const alpha = false);
	CImage(SColor const & Color, bool const Alpha = false);
	~CImage();

	int const getWidth() const;
	int const getHeight() const;
	unsigned char const * const getImageData() const;
	unsigned char * getImageData();
	bool const hasAlpha() const;

};

#endif
