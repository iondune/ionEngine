
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionFramework.h>
#include <ionWindow.h>

#include <simpleini/SimpleIni.h>


namespace ion
{


	class CDefaultApplication : public IEventListener
	{

	public:

		struct SSettings
		{
			vec2i WindowSize = vec2i(1980, 1080);
			vec2i WindowPosition = vec2i(20, 50);
			EWindowType WindowType = EWindowType::Windowed;
			float FontSize = 18.f;
			float UIScale = 1.f;
		};

		void LoadSettings();

	protected:

		SSettings ApplicationSettings;

		virtual void LoadAdditionalSettings(CSimpleIniA * ConfigFile);

	};

}
