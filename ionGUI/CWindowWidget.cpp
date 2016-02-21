
#include "CWindowWidget.h"


namespace ion
{
	namespace GUI
	{

		void CWindowWidget::DrawIfVisible()
		{
			if (IsVisible)
			{
				Draw();
			}
		}

		void CWindowWidget::ToggleVisibility()
		{
			IsVisible = ! IsVisible;
		}

	}
}
