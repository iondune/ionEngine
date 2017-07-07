
#include "ionLogger.h"

#ifdef ION_CONFIG_WINDOWS
#include <Windows.h>
#endif


namespace ion
{

	Log::StandardOutput::StandardOutput(std::ostream & Stream)
		: Stream(Stream)
	{}

	void Log::StandardOutput::Write(string const & Message)
	{
		Stream << Message << std::endl;
	}

	void Log::WindowsLogOutput::Write(string const & Message)
	{
#ifdef ION_CONFIG_WINDOWS
		OutputDebugString(Message.c_str());
		OutputDebugString("\n");
#endif
	}

	vector<string> const & Log::GetMessages()
	{
		return AllLoggedMessages();
	}

	vector<string> const & Log::GetMessages(ELogChannel const Which)
	{
		return GetChannel(Which).Messages;
	}

	vector<pair<string, int>> const & Log::GetMessagesDetail(ELogChannel const Which)
	{
		return GetChannel(Which).GetMessagesDetail();
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
#ifdef ION_CONFIG_WINDOWS
		AddOutputToAllChannels(new WindowsLogOutput());
#endif
	}

	void Log::Clear()
	{
		AllLoggedMessages().clear();
		GetChannel(ELogChannel::Info).Messages.clear();
		GetChannel(ELogChannel::Info).MessageMap.clear();
		GetChannel(ELogChannel::Warn).Messages.clear();
		GetChannel(ELogChannel::Warn).MessageMap.clear();
		GetChannel(ELogChannel::Error).Messages.clear();
		GetChannel(ELogChannel::Error).MessageMap.clear();
	}

	Log::Channel::Channel(string const & Label)
	{
		this->Label = Label;
	}

	bool Log::Channel::WriteMessage(string const & ToWrite)
	{
		auto LookUp = MessageMap.find(ToWrite);

		for (Output * Out : WriteTo)
		{
			Out->Write(ToWrite);
		}

		if (LookUp != MessageMap.end())
		{
			LookUp->second ++;

			return false;
		}
		else
		{
			MessageMap[ToWrite] = 1;
			Messages.push_back(ToWrite);

			return true;
		}
	}

	vector<pair<string, int>> const & Log::Channel::GetMessagesDetail()
	{
		MessagesDetail.clear();

		for (auto const & Message : Messages)
		{
			MessagesDetail.push_back(make_pair(Message, MessageMap[Message]));
		}

		return MessagesDetail;
	}

	Log::Channel & Log::GetChannel(ELogChannel const Which)
	{
		static Channel Info("Info");
		static Channel Warn("Warn");
		static Channel Error("Error");

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
		if (GetChannel(Which).WriteMessage(Message))
		{
			AllLoggedMessages().push_back(GetChannelLabel(Which) + ": " + Message);
		}
	}

	vector<string> & Log::AllLoggedMessages()
	{
		static vector<string> AllLoggedMessages;
		return AllLoggedMessages;
	}
}
