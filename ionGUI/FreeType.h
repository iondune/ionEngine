
#pragma once

// FreeType Headers
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

// OpenGL Headers 
#define NOMINMAX
#include <windows.h> // (the GL headers need it)
#include <GL/gl.h>
#include <GL/glu.h>

// STL
#include <vector>
#include <string>
#include <stdexcept>


namespace freetype
{
	using std::vector;
	using std::string;

	/// This holds all of the information related to any
	/// freetype font that we want to create.  
	struct font_data
	{
		float h;			///< Holds the height of the font.
		GLuint * textures;	///< Holds the texture id's 
		GLuint list_base;	///< Holds the first display list id
		FT_Library library;
		FT_Face face;
		
		/// The init function will create a font of
		/// of the height h from the file fname.
		void init(const char * fname, unsigned int h);

		/// Free all the resources assosiated with the font.
		void clean();
	};

	void measure(font_data const & ft_font, int * width, int * height, char const * fmt, ...);

	/// The flagship function of the library - this thing will print
	/// out text at window coordinates x,y, using the font ft_font.
	/// The current modelview matrix will also be applied to the text. 
	void print(const font_data &ft_font, float x, float y, const char *fmt, ...) ;

}
