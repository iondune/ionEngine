
#include "CDefaultApplication.h"

#include <simpleini/SimpleIni.h>


namespace ion
{

	void CDefaultApplication::LoadSettings()
	{
		CSimpleIniA ConfigFile;
		ConfigFile.LoadFile("ionEngine.ini");

		ApplicationSettings.WindowSize.X = ConfigFile.GetLongValue("window", "width", ApplicationSettings.WindowSize.X);
		ApplicationSettings.WindowSize.Y = ConfigFile.GetLongValue("window", "height", ApplicationSettings.WindowSize.Y);

		bool Fullscreen = ConfigFile.GetBoolValue("window", "fullscreen", false);
		ApplicationSettings.WindowType = (Fullscreen ? EWindowType::Fullscreen : EWindowType::Windowed);
	}

}
