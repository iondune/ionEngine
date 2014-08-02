
#include <ionConfig.h>

#ifdef _ION_CONFIG_USE_GWEN

#include "OpenGL3Font.h"
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

			pFont->data = IFont::init(Gwen::Utility::UnicodeToString(pFont->facename).c_str(), pFont->size);
		}

		void OpenGL3Font::RenderText(Gwen::Font * pFont, Gwen::Point pos, Gwen::UnicodeString const & text)
		{
			LoadFont(pFont);
			Translate(pos.x, pos.y);
			Gwen::String String = Gwen::Utility::UnicodeToString(text);

			IFont * Font = (IFont *) pFont->data;
			glDisable(GL_SCISSOR_TEST);
			Font->print(pos.x, pos.y, String.c_str());
			glEnable(GL_SCISSOR_TEST);
		}

		Gwen::Point OpenGL3Font::MeasureText(Gwen::Font * pFont, Gwen::UnicodeString const & text)
		{
			LoadFont(pFont);

			Gwen::String String = Gwen::Utility::UnicodeToString(text);

			Gwen::Point pos;
			IFont * Font = (IFont *) pFont->data;
			Font->measure(& pos.x, & pos.y, String.c_str());

			pos.y *= Scale();

			return pos;
		}
	}
}

#endif
