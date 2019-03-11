
#include "CDefaultApplication.h"

#include "CControlPanel.h"
#include "CAssetManager.h"


namespace ion
{

	void CDefaultApplication::LoadSettings()
	{
		ControlPanel->AddComponent(AssetManager.Get());

		CSimpleIniA ConfigFile;
		if (File::Exists("ionEngine.ini"))
		{
			ConfigFile.LoadFile("ionEngine.ini");
		}
		else
		{
			ConfigFile.LoadFile((string(ION_PROJECT_BASE_DIRECTORY) + "ionEngine.ini").c_str());
		}

		ApplicationSettings.WindowSize.X = ConfigFile.GetLongValue("window", "width", ApplicationSettings.WindowSize.X);
		ApplicationSettings.WindowSize.Y = ConfigFile.GetLongValue("window", "height", ApplicationSettings.WindowSize.Y);

		ApplicationSettings.WindowPosition.X = ConfigFile.GetLongValue("window", "x", ApplicationSettings.WindowPosition.X);
		ApplicationSettings.WindowPosition.Y = ConfigFile.GetLongValue("window", "y", ApplicationSettings.WindowPosition.Y);

		ApplicationSettings.WindowMonitor = ConfigFile.GetLongValue("window", "monitor", ApplicationSettings.WindowMonitor);

		ApplicationSettings.FontSize = (float) ConfigFile.GetDoubleValue("window", "fontsize", ApplicationSettings.FontSize);
		ApplicationSettings.UIScale = (float) ConfigFile.GetDoubleValue("window", "uiscale", ApplicationSettings.UIScale);

		bool Fullscreen = ConfigFile.GetBoolValue("window", "fullscreen", false);
		ApplicationSettings.WindowType = (Fullscreen ? EWindowType::Fullscreen : EWindowType::Windowed);

		string VsynnModeString = ConfigFile.GetValue("window", "vsync", "");
		if (VsynnModeString == "default")
		{
			ApplicationSettings.VsyncMode = EVsyncMode::Default;
		}
		else if (VsynnModeString == "default")
		{
			ApplicationSettings.VsyncMode = EVsyncMode::Off;
		}
		else if (VsynnModeString == "default")
		{
			ApplicationSettings.VsyncMode = EVsyncMode::On;
		}
		else if (VsynnModeString.length())
		{
			Log::Error("Unknown vsycn mode string: %s", VsynnModeString);
		}

		LoadAdditionalSettings(&ConfigFile);
	}

	CWindow * CDefaultApplication::CreateWindowFromSettings(string const & Title)
	{
		CWindow * Window = nullptr;
		SingletonPointer<ion::CWindowManager> WindowManager;

		if (ApplicationSettings.WindowMonitor >= 0)
		{
			Window = WindowManager->CreateWindowOnMonitor(ApplicationSettings.WindowMonitor, Title, ApplicationSettings.VsyncMode);
		}
		else
		{
			Window = WindowManager->CreateWindow(ApplicationSettings.WindowSize, Title, ApplicationSettings.WindowType, ApplicationSettings.VsyncMode);
			Window->SetPosition(ApplicationSettings.WindowPosition);
		}

		return Window;
	}

	void CDefaultApplication::LoadAdditionalSettings(CSimpleIniA * ConfigFile)
	{

	}

	void CDefaultApplication::DrawGUI()
	{
		ControlPanel->Display();
	}

	void CDefaultApplication::OnEvent(IEvent & Event)
	{
		if (InstanceOf<SKeyboardEvent>(Event))
		{
			SKeyboardEvent KeyboardEvent = As<SKeyboardEvent>(Event);

			if (! KeyboardEvent.Pressed)
			{
				switch (KeyboardEvent.Key)
				{
				case EKey::Grave:
					ToggleBool(ControlPanel->IsVisible);
					break;
				}
			}
		}
	}

}
