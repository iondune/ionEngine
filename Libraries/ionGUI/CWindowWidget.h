
#pragma once

#include <ionCore.h>


namespace ion
{
	namespace GUI
	{

		class CWindowWidget
		{

		public:

			virtual void DrawGUI() = 0;

			void DrawGUIIfVisible();
			void ToggleGUIVisibility();

		protected:

			bool IsVisible = false;

		};

	}
}
