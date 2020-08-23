
#include "ionLogger.h"

#ifdef ION_CONFIG_WINDOWS
#include <Windows.h>
#endif

#include <fstream>


namespace ion
{

	Log::StandardOutput::StandardOutput(std::ostream & Stream)
		: Stream(Stream)
	{}

	void Log::StandardOutput::Write(ELogChannel const Channel, string const & Message)
	{
#ifdef ION_CONFIG_WINDOWS
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		WORD wOldColorAttrs;
		CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

		GetConsoleScreenBufferInfo(h, &csbiInfo);
		wOldColorAttrs = csbiInfo.wAttributes;

		if (Channel == ELogChannel::Error)
		{
			SetConsoleTextAttribute(h, BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
		else if (Channel == ELogChannel::Warn)
		{
			SetConsoleTextAttribute(h, BACKGROUND_RED | BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
#endif

		Stream << Message << std::endl;

#ifdef ION_CONFIG_WINDOWS
		SetConsoleTextAttribute(h, wOldColorAttrs);
#endif
	}

	Log::FileOutput::FileOutput(std::string const & FileName)
	{
		File = new std::ofstream(FileName, std::ios::out);
	}

	Log::FileOutput::~FileOutput()
	{
		if (File)
		{
			File->close();
			delete File;
		}
	}

	void Log::FileOutput::Write(ELogChannel const Channel, string const & Message)
	{
		if (File && File->is_open())
		{
			*File << Message << std::endl;
		}
	}

	void Log::WindowsLogOutput::Write(ELogChannel const Channel, string const & Message)
	{
#ifdef ION_CONFIG_WINDOWS
		int wcharsCount =  MultiByteToWideChar(CP_UTF8 , 0 , Message.c_str() , -1, NULL, 0);
		wchar_t * wstr = new wchar_t[wcharsCount];
		MultiByteToWideChar(CP_UTF8, 0, Message.c_str(), -1, wstr, wcharsCount);
		OutputDebugString(wstr);
		delete[] wstr;

		OutputDebugString(L"\n");
#endif
	}

	void Log::AddOutput(ELogChannel const Which, Output * Out)
	{
		GetChannel(Which).WriteTo.push_back(Out);
	}

	void Log::AddOutputToAllChannels(Output * Out)
	{
		GetChannel(ELogChannel::Error).WriteTo.push_back(Out);
		GetChannel(ELogChannel::Warn).WriteTo.push_back(Out);
		GetChannel(ELogChannel::Info).WriteTo.push_back(Out);
	}

	void Log::AddDefaultOutputs()
	{
		AddOutput(ELogChannel::Error, new StandardOutput(std::cerr));
		AddOutput(ELogChannel::Warn, new StandardOutput(std::cerr));
		AddOutput(ELogChannel::Info, new StandardOutput(std::cout));
		
		AddOutputToAllChannels(new FileOutput("ionLogger.txt"));
#ifdef ION_CONFIG_WINDOWS
		AddOutputToAllChannels(new WindowsLogOutput());
#endif
	}

	Log::Channel::Channel(ELogChannel const which, string const & Label)
		: Which(which)
	{
		this->Label = Label;
	}

	void Log::Channel::WriteMessage(string const & ToWrite)
	{
		for (Output * Out : WriteTo)
		{
			Out->Write(Which, ToWrite);
		}
	}
	Log::Channel & Log::GetChannel(ELogChannel const Which)
	{
		static Channel Info(ELogChannel::Info, "Info");
		static Channel Warn(ELogChannel::Warn, "Warn");
		static Channel Error(ELogChannel::Error, "Error");

		switch (Which)
		{
		default:
		case ELogChannel::Info:
			return Info;
		case ELogChannel::Warn:
			return Warn;
		case ELogChannel::Error:
			return Error;
		}
	}

	string Log::GetChannelLabel(ELogChannel const Which)
	{
		return GetChannel(Which).Label;
	}

	void Log::WriteInternal(ELogChannel const Which, std::string const & Message)
	{
		GetChannel(Which).WriteMessage(Message);
	}

}
