
#pragma once

#include <ionCore.h>


namespace ion
{

	class IControlComponent
	{

	public:

		virtual string GetName() = 0;
		virtual void DrawGUIControls() = 0;

		bool IsOpen = false;

	};

	class CControlPanel : public Singleton<CControlPanel>
	{

	public:

		void AddComponent(IControlComponent * component);
		void Display();

		bool IsVisible = false;

	protected:

		vector<IControlComponent *> Components;

	};

}
