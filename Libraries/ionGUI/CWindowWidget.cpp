
#include "CWindowWidget.h"


namespace ion
{
	namespace GUI
	{

		void CWindowWidget::DrawGUIIfVisible()
		{
			if (IsVisible)
			{
				DrawGUI();
			}
		}

		void CWindowWidget::ToggleGUIVisibility()
		{
			IsVisible = ! IsVisible;
		}

	}
}
