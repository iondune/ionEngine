
#pragma once

#include <ionCore.h>
#include <ionWindow.h>

#include <simpleini/SimpleIni.h>
#undef CreateWindow


namespace ion
{

	class CControlPanel;
	class CAssetManager;

	class CDefaultApplication : public IEventListener
	{

	public:

		struct SSettings
		{
			int WindowMonitor = -1;
			vec2i WindowSize = vec2i(1980, 1080);
			vec2i WindowPosition = vec2i(20, 50);
			EWindowType WindowType = EWindowType::Windowed;
			EVsyncMode VsyncMode = EVsyncMode::Default;
			float FontSize = 18.f;
			float UIScale = 1.f;
		};

		void LoadSettings();
		CWindow * CreateWindowFromSettings(string const & Title);

		void DrawGUI();
		void OnEvent(IEvent & Event);

	protected:

		SSettings ApplicationSettings;

		virtual void LoadAdditionalSettings(CSimpleIniA * ConfigFile);

		SingletonPointer<CControlPanel> ControlPanel;

	private:

		SingletonPointer<CAssetManager> AssetManager;

	};

}
