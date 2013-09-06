
#pragma once

#include "OpenGL3.h"


namespace Gwen
{
	namespace Renderer
	{
		class OpenGL3Font : public OpenGL3
		{

		public:

			OpenGL3Font(vec2i const & Size);

			void RenderText(Gwen::Font* pFont, Gwen::Point pos, const Gwen::UnicodeString & text);
			Gwen::Point MeasureText(Gwen::Font* pFont, const Gwen::UnicodeString & text);

		protected:

			void LoadFont(Gwen::Font * pFont);

		};
	}
}
