
#pragma once

#include <ionEngine.h>


namespace ion
{
	namespace GUI
	{

		class CWindowWidget
		{

		public:

			virtual void Draw() = 0;

			void DrawIfVisible();
			void ToggleVisibility();

		protected:

			bool IsVisible = false;

		};

	}
}
