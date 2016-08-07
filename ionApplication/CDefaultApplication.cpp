
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

		ApplicationSettings.WindowPosition.X = ConfigFile.GetLongValue("window", "x", ApplicationSettings.WindowPosition.X);
		ApplicationSettings.WindowPosition.Y = ConfigFile.GetLongValue("window", "y", ApplicationSettings.WindowPosition.Y);

		ApplicationSettings.FontSize = (float) ConfigFile.GetDoubleValue("window", "fontsize", ApplicationSettings.FontSize);
		ApplicationSettings.UIScale = (float) ConfigFile.GetDoubleValue("window", "uiscale", ApplicationSettings.UIScale);

		bool Fullscreen = ConfigFile.GetBoolValue("window", "fullscreen", false);
		ApplicationSettings.WindowType = (Fullscreen ? EWindowType::Fullscreen : EWindowType::Windowed);
	}

}
