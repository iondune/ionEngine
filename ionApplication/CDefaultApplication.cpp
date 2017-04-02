
#include "CDefaultApplication.h"


namespace ion
{

	void CDefaultApplication::LoadSettings()
	{
		CSimpleIniA ConfigFile;
		ConfigFile.LoadFile("ionEngine.ini");

		ApplicationSettings.WindowSize.X = ConfigFile.GetLongValue("window", "width", ApplicationSettings.WindowSize.X);
		ApplicationSettings.WindowSize.Y = ConfigFile.GetLongValue("window", "height", ApplicationSettings.WindowSize.Y);

		ApplicationSettings.WindowPosition.X = ConfigFile.GetLongValue("window", "x", ApplicationSettings.WindowPosition.X);
		ApplicationSettings.WindowPosition.Y = ConfigFile.GetLongValue("window", "y", ApplicationSettings.WindowPosition.Y);

		ApplicationSettings.WindowMonitor = ConfigFile.GetLongValue("window", "monitor", ApplicationSettings.WindowMonitor);

		ApplicationSettings.FontSize = (float) ConfigFile.GetDoubleValue("window", "fontsize", ApplicationSettings.FontSize);
		ApplicationSettings.UIScale = (float) ConfigFile.GetDoubleValue("window", "uiscale", ApplicationSettings.UIScale);

		bool Fullscreen = ConfigFile.GetBoolValue("window", "fullscreen", false);
		ApplicationSettings.WindowType = (Fullscreen ? EWindowType::Fullscreen : EWindowType::Windowed);

		LoadAdditionalSettings(&ConfigFile);
	}

	CWindow * CDefaultApplication::CreateWindowFromSettings(string const & Title)
	{
		CWindow * Window = nullptr;
		SingletonPointer<ion::CWindowManager> WindowManager;

		if (ApplicationSettings.WindowMonitor >= 0)
		{
			Window = WindowManager->CreateWindowOnMonitor(ApplicationSettings.WindowMonitor, Title);
		}
		else
		{
			Window = WindowManager->CreateWindow(ApplicationSettings.WindowSize, Title, ApplicationSettings.WindowType);
			Window->SetPosition(ApplicationSettings.WindowPosition);
		}

		return Window;
	}

	void CDefaultApplication::LoadAdditionalSettings(CSimpleIniA * ConfigFile)
	{

	}

}
