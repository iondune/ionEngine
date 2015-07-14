
#pragma once

#include "ionStandardLibrary.h"

#include <tinyformat.h>


enum class ELogChannel
{
	Info,
	Warn,
	Error
};

class Log
{

public:

	template <typename... Args>
	static void Info(char const * const Format, Args const &... args)
	{
#ifndef _ION_CONFIG_SUPPRESS_LOG
		Write(ELogChannel::Info, Format, args...);
#endif
	}

	template <typename... Args>
	static void Warn(char const * const Format, Args const &... args)
	{
#ifndef _ION_CONFIG_SUPPRESS_LOG
		Write(ELogChannel::Warn, Format, args...);
#endif
	}

	template <typename... Args>
	static void Error(char const * const Format, Args const &... args)
	{
#ifndef _ION_CONFIG_SUPPRESS_LOG
		Write(ELogChannel::Error, Format, args...);
#endif
	}

	template <typename... Args>
	static void Write(ELogChannel const Channel, char const * const Format, Args const &... args)
	{
#ifndef _ION_CONFIG_SUPPRESS_LOG
		WriteInternal(Channel, tfm::format(Format, args...));
#endif
	}

	static vector<string> const & GetMessages()
	{
		return AllLoggedMessages();
	}

	static vector<string> const & GetMessages(ELogChannel const Which)
	{
		return GetChannel(Which).Messages;
	}

	static vector<pair<string, int>> const & GetMessagesDetail(ELogChannel const Which)
	{
		return GetChannel(Which).GetMessagesDetail();
	}

	static void SetWriteMessages(bool const Write)
	{
		GetChannel(ELogChannel::Info).Write = Write;
		GetChannel(ELogChannel::Warn).Write = Write;
		GetChannel(ELogChannel::Error).Write = Write;
	}

	static void SetWriteMessages(ELogChannel const Which, bool const Write)
	{
		GetChannel(Which).Write = Write;
	}

	static void Clear()
	{
		AllLoggedMessages().clear();
		GetChannel(ELogChannel::Info).Messages.clear();
		GetChannel(ELogChannel::Info).MessageMap.clear();
		GetChannel(ELogChannel::Warn).Messages.clear();
		GetChannel(ELogChannel::Warn).MessageMap.clear();
		GetChannel(ELogChannel::Error).Messages.clear();
		GetChannel(ELogChannel::Error).MessageMap.clear();
	}

protected:

	class Channel
	{

	public:

		string Label;
		bool Write;
		std::ostream * WriteTo;
		vector<string> Messages;
		vector<pair<string, int>> MessagesDetail;
		unordered_map<string, int> MessageMap;

		Channel(string const & Label, bool Write, std::ostream * WriteTo)
		{
			this->Label = Label;
			this->Write = Write;
			this->WriteTo = WriteTo;
		}

		//! \return true if this is a new message, false if not
		bool WriteMessage(string const & ToWrite)
		{
			auto LookUp = MessageMap.find(ToWrite);

			if (LookUp != MessageMap.end())
			{
				LookUp->second ++;

				return false;
			}
			else
			{
				MessageMap[ToWrite] = 1;
				Messages.push_back(ToWrite);
				if (Write)
					(*WriteTo) << ToWrite << endl; // LCOV_EXCL_LINE

				return true;
			}
		}

		vector<pair<string, int>> const & GetMessagesDetail()
		{
			MessagesDetail.clear();

			for (auto const & Message : Messages)
				MessagesDetail.push_back(make_pair(Message, MessageMap[Message]));

			return MessagesDetail;
		}

	};

	static Channel & GetChannel(ELogChannel const Which)
	{
		static Channel Info("Info", true, & cout);
		static Channel Warn("Warn", true, & cerr);
		static Channel Error("Error", true, & cerr);

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

	static string GetChannelLabel(ELogChannel const Which)
	{
		return GetChannel(Which).Label;
	}

	static void WriteInternal(ELogChannel const Which, std::string const & Message)
	{
		if (GetChannel(Which).WriteMessage(Message))
			AllLoggedMessages().push_back(GetChannelLabel(Which) + ": " + Message);
	}

	static vector<string> & AllLoggedMessages()
	{
		static vector<string> AllLoggedMessages;
		return AllLoggedMessages;
	}

};
