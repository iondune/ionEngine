
#include "FreeType.h"

// FreeType Headers
#include <ft2build.h>
#include <freetype.h>
#include <ftglyph.h>
#include <ftoutln.h>
#include <fttrigon.h>

// OpenGL Headers 
#include <GL/glew.h>


class CFont : public IFont
{

public:
	
	static IFont * init(const char * fname, unsigned int h);

	virtual ~CFont();

	virtual void measure(int * width, int * height, char const * fmt, ...);

	virtual void print(float x, float y, const char *fmt, ...) ;

protected:

	float Height;			///< Holds the height of the font.
	float LineSpacing = 1.5f;
	GLuint * textures;	///< Holds the texture id's 
	GLuint list_base;	///< Holds the first display list id
	FT_Library library;
	FT_Face face;

};


int NextLargerPowerOfTwo(int const a);
void get_glyph_size(FT_Face face, char ch, int font_height, int * width, int * height);
void make_dlist(FT_Face face, char ch, GLuint list_base, GLuint * tex_base);


IFont * IFont::init(const char * fname, unsigned int h)
{
	return CFont::init(fname, h);
}

IFont * CFont::init(const char * fname, unsigned int h)
{
	FT_Library library;
	if (FT_Init_FreeType(& library))
	{
		cerr << "FT_Init_FreeType failed" << endl;
		return nullptr;
	}

	FT_Face face;
	if (FT_New_Face(library, fname, 0, & face))
	{
		cerr << "FT_New_Face failed (there is probably a problem with your font file)" << endl;
		return nullptr;
	}

	// For some twisted reason, Freetype measures font size
	// in terms of 1/64ths of pixels.  Thus, to make a font
	// h pixels high, we need to request a size of h*64.
	FT_Set_Char_Size(face, h*64, h*64, 96, 96);

	GLuint list_base = glGenLists(128);

	GLuint * textures = new GLuint[128];
	glGenTextures(128, textures);

	for (unsigned char i = 0; i < 128; ++ i)
		make_dlist(face, i, list_base, textures);

	CFont * Font = new CFont();
	Font->Height = (float) h;
	Font->textures = textures;
	Font->list_base = list_base;
	Font->library = library;
	Font->face = face;

	return Font;
}

CFont::~CFont()
{
	glDeleteLists(list_base, 128);
	glDeleteTextures(128, textures);
	delete [] textures;

	FT_Done_Face(face);
	FT_Done_FreeType(library);
}

/// A fairly straight forward function that pushes
/// a projection matrix that will make object world
/// coordinates identical to window coordinates.
inline void pushScreenCoordinateMatrix()
{
	glPushAttrib(GL_TRANSFORM_BIT);
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(viewport[0], viewport[2], viewport[1], viewport[3]);
	glPopAttrib();
}

/// Pops the projection matrix without changing the current
/// MatrixMode.
inline void pop_projection_matrix()
{
	glPushAttrib(GL_TRANSFORM_BIT);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPopAttrib();
}

void CFont::measure(int * width, int * height, char const * fmt, ...)
{
	if (! fmt)
		return;

	char text[16386];
	va_list ap;

	va_start(ap, fmt);
	vsprintf(text, fmt, ap);
	va_end(ap);

	*width = 0;
	*height = 0;

	int x, y;
	vector<string> lines = String::SeparateLines(text);
	for (unsigned int i = 0; i < lines.size(); ++ i)
	{
		for (unsigned int t = 0; t < lines[i].size(); ++ t)
		{
			get_glyph_size(this->face, lines[i][t], (int) Height, & x, & y);
			if (y > * height)
				*height = y;
			*width += x;
		}
	}
	*height += (int) ((lines.size() - 1) * Height);
}

void CFont::print(float x, float y, const char * fmt, ...)
{
	if (! fmt)
		return;

	// We want a coordinate system where things coresponding to window pixels.
	pushScreenCoordinateMatrix();

	char text[16386];
	va_list ap;

	va_start(ap, fmt);
	vsprintf(text, fmt, ap);
	va_end(ap);


	glPushAttrib(GL_LIST_BIT | GL_CURRENT_BIT  | GL_ENABLE_BIT | GL_TRANSFORM_BIT);
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	

	GLuint font = list_base;
	glListBase(font);

	float modelview_matrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);
		
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	//This is where the text display actually happens.
	//For each line of text we reset the modelview matrix
	//so that the line's text will start in the correct position.
	//Notice that we need to reset the matrix, rather than just translating
	//down by h. This is because when each character is
	//draw it modifies the current matrix so that the next character
	//will be drawn immediatly after it.
	vector<string> lines = String::SeparateLines(text);
	for (unsigned int i = 0; i < lines.size(); ++ i)
	{
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(x, viewport[3] - y - 2 - Height * LineSpacing *i - Height, 0);
		glMultMatrixf(modelview_matrix);

		// The commented out raster position stuff can be useful if you need to
		// know the length of the text that you are creating.
		// If you decide to use it make sure to also uncomment the glBitmap command
		// in make_dlist().
		// glRasterPos2f(0, 0);
		glCallLists(lines[i].length(), GL_UNSIGNED_BYTE, lines[i].c_str());
		// float rpos[4];
		// glGetFloatv(GL_CURRENT_RASTER_POSITION, rpos);
		// float len = x - rpos[0];

		glPopMatrix();
	}

	glPopAttrib();
	pop_projection_matrix();
}

	
/// This function gets the first power of 2 >= the
/// int that we pass it.
int NextLargerPowerOfTwo(int const a)
{
	int rval = 2;
	while (rval < a)
		rval <<= 1;
	return rval;
}

struct GlyphInfo
{
	GlyphInfo(FT_Face Face, char Ch)
	{
		if (FT_Load_Glyph(Face, FT_Get_Char_Index(Face, Ch), FT_LOAD_DEFAULT))
		{
			cerr << "FT_Load_Glyph failed" << endl;
			return;
		}

		if (FT_Get_Glyph(Face->glyph, & Glyph))
		{
			cerr << "FT_Get_Glyph failed" << endl;
			return;
		}

		FT_Glyph_To_Bitmap(& Glyph, ft_render_mode_normal, 0, 1);
		FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph) Glyph;
		Bitmap = bitmap_glyph->bitmap;

		Top = bitmap_glyph->top;
		Left = bitmap_glyph->left;
		BitmapRows = Bitmap.rows;
		BitmapWidth = Bitmap.width;
		Advance = Face->glyph->advance.x / 64;
	}

	void CreateImage()
	{
		ImageWidth = NextLargerPowerOfTwo(Bitmap.width);
		ImageHeight = NextLargerPowerOfTwo(Bitmap.rows);
		
		// Two Channels
		ImageData = new byte[2 * ImageWidth * ImageHeight];

		for (int j = 0; j <ImageHeight ; ++ j)
		{
			for (int i = 0; i < ImageWidth; ++ i)
			{
				// Luminocity
				ImageData[2 * (i + j * ImageWidth)] = 255;

				// Alpha
				if (i >= Bitmap.width || j >= Bitmap.rows)
					ImageData[2 * (i + j * ImageWidth) + 1] = 0;
				else
					ImageData[2 * (i + j * ImageWidth) + 1] = Bitmap.buffer[i + Bitmap.width * j];
			}
		}
	}

	~GlyphInfo()
	{
		if (ImageData)
			delete [] ImageData;
		FT_Done_Glyph(Glyph);
	}

	byte * ImageData = nullptr;
	
	int ImageWidth = 0;
	int ImageHeight = 0;

	int Top = 0;
	int Left = 0;
	int BitmapRows = 0;
	int BitmapWidth = 0;
	int Advance = 0;
	
	FT_Glyph Glyph;
	FT_Bitmap Bitmap;
};

void get_glyph_size(FT_Face face, char ch, int font_height, int * width, int * height)
{
	GlyphInfo Glyph(face, ch);

	*width = Glyph.Advance;
	*height = Glyph.BitmapRows;
	*height += font_height - Glyph.Top;
}

void make_dlist(FT_Face face, char ch, GLuint list_base, GLuint * tex_base)
{
	GlyphInfo Glyph(face, ch);
	Glyph.CreateImage();

	glBindTexture(GL_TEXTURE_2D, tex_base[ch]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Glyph.ImageWidth, Glyph.ImageHeight,
		0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, Glyph.ImageData);

	// So now we can create the display list
	glNewList(list_base + ch, GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D, tex_base[ch]);
	glPushMatrix();

	// first we need to move over a little so that
	// the character has the right amount of space
	// between it and the one before it.
	glTranslatef((float) Glyph.Left, 0, 0);

	// Now we move down a little in the case that the
	// bitmap extends past the bottom of the line
	// (this is only true for characters like 'g' or 'y'.
	glTranslatef(0, (float) Glyph.Top - Glyph.BitmapRows, 0);

	// Now we need to account for the fact that many of
	// our textures are filled with empty padding space.
	// We figure what portion of the texture is used by
	// the actual character and store that information in
	// the x and y variables, then when we draw the
	// quad, we will only reference the parts of the texture
	// that we contain the character itself.
	float x = (float) Glyph.BitmapWidth / (float) Glyph.ImageWidth,
		y = (float) Glyph.BitmapRows / (float) Glyph.ImageHeight;

	// Here we draw the texturemaped quads.
	// The bitmap that we got from FreeType was not
	// oriented quite like we would like it to be,
	// so we need to link the texture to the quad
	// so that the result will be properly aligned.
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex2f(0, (float) Glyph.BitmapRows);
	glTexCoord2d(0, y); glVertex2f(0, 0);
	glTexCoord2d(x, y); glVertex2f((float) Glyph.BitmapWidth, 0);
	glTexCoord2d(x, 0); glVertex2f((float) Glyph.BitmapWidth, (float) Glyph.BitmapRows);
	glEnd();
	glPopMatrix();
	glTranslatef((float) Glyph.Advance, 0, 0);

	// Finish the display list
	glEndList();
}
