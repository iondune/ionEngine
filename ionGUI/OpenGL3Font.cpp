
#include <ionConfig.h>

#ifdef _ION_CONFIG_USE_GWEN

#include "OpenGL3Font.h"

#include "Gwen.h"

#include <math.h>
#include "GL/glew.h"

#include "FreeType.h"


namespace Gwen
{
	namespace Renderer
	{
		OpenGL3Font::OpenGL3Font(vec2i const & Size)
			: Gwen::Renderer::OpenGL3(Size)
		{}

		void OpenGL3Font::LoadFont(Gwen::Font * pFont)
		{
			if (pFont->data)
				return;

			freetype::font_data * font;

			pFont->data = font = new freetype::font_data;
			font->init(Gwen::Utility::UnicodeToString(pFont->facename).c_str(), pFont->size);
		}

		void OpenGL3Font::RenderText(Gwen::Font * pFont, Gwen::Point pos, Gwen::UnicodeString const & text)
		{
			LoadFont(pFont);
			Translate(pos.x, pos.y);
			Gwen::String String = Gwen::Utility::UnicodeToString(text);

			freetype::print(* (freetype::font_data *) pFont->data, pos.x, pos.y, String.c_str());
		}

		Gwen::Point OpenGL3Font::MeasureText(Gwen::Font * pFont, Gwen::UnicodeString const & text)
		{
			LoadFont(pFont);

			Gwen::String String = Gwen::Utility::UnicodeToString(text);

			Gwen::Point pos;
			freetype::measure(* (freetype::font_data *) pFont->data, & pos.x, & pos.y, String.c_str());
			return pos;
		}
	}
}

#endif
