
/*!
\file ionLogger.h
\ingroup ionCore
\brief Logging class
*/


#pragma once

#include "ionTypes.h"
#include "String.h"

#ifdef ION_CONFIG_WINDOWS
#include <Windows.h>
#endif


namespace ion
{

	//! \brief Channels used by Log
	//! \ingroup ionCore
	enum class ELogChannel
	{
		Error = 0,
		Warn = 1,
		Info = 2
	};

	//! \brief Logging class
	//! \ingroup ionCore
	class Log
	{

	public:

		class Output
		{

		public:

			virtual void Write(string const & Message) = 0;

		};

		class StandardOutput : public Output
		{

		public:

			StandardOutput(std::ostream & Stream)
				: Stream(Stream)
			{}

			virtual void Write(string const & Message)
			{
				Stream << Message << std::endl;
			}

		private:

			std::ostream & Stream;

		};

#ifdef ION_CONFIG_WINDOWS
		class DebugLogOutput : public Output
		{

		public:

			virtual void Write(string const & Message)
			{
				OutputDebugString(Message.c_str());
				OutputDebugString("\n");
			}

		};
#endif

		template <typename... Args>
		static void Info(char const * const Format, Args const &... args)
		{
			Write(ELogChannel::Info, Format, args...);
		}

		template <typename... Args>
		static void Warn(char const * const Format, Args const &... args)
		{
			Write(ELogChannel::Warn, Format, args...);
		}

		template <typename... Args>
		static void Error(char const * const Format, Args const &... args)
		{
			Write(ELogChannel::Error, Format, args...);
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

		static void AddOutput(ELogChannel const Which, Output * Out)
		{
			GetChannel(Which).WriteTo.push_back(Out);
		}

		static void AddOutputToAllChannels(Output * Out)
		{
			GetChannel(ELogChannel::Error).WriteTo.push_back(Out);
			GetChannel(ELogChannel::Warn).WriteTo.push_back(Out);
			GetChannel(ELogChannel::Info).WriteTo.push_back(Out);
		}

		static void AddDefaultOutputs()
		{
			AddOutput(ELogChannel::Error, new StandardOutput(std::cerr));
			AddOutput(ELogChannel::Warn, new StandardOutput(std::cerr));
			AddOutput(ELogChannel::Info, new StandardOutput(std::cout));
#ifdef ION_CONFIG_WINDOWS
			AddOutputToAllChannels(new DebugLogOutput());
#endif
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
			vector<Output *> WriteTo;
			vector<string> Messages;
			vector<pair<string, int>> MessagesDetail;
			unordered_map<string, int> MessageMap;

			Channel(string const & Label)
			{
				this->Label = Label;
			}

			//! \return true if this is a new message, false if not
			bool WriteMessage(string const & ToWrite)
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

			vector<pair<string, int>> const & GetMessagesDetail()
			{
				MessagesDetail.clear();

				for (auto const & Message : Messages)
				{
					MessagesDetail.push_back(make_pair(Message, MessageMap[Message]));
				}

				return MessagesDetail;
			}

		};

		static Channel & GetChannel(ELogChannel const Which)
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

		static string GetChannelLabel(ELogChannel const Which)
		{
			return GetChannel(Which).Label;
		}

		static void WriteInternal(ELogChannel const Which, std::string const & Message)
		{
			if (GetChannel(Which).WriteMessage(Message))
			{
				AllLoggedMessages().push_back(GetChannelLabel(Which) + ": " + Message);
			}
		}

		static vector<string> & AllLoggedMessages()
		{
			static vector<string> AllLoggedMessages;
			return AllLoggedMessages;
		}

	};

}
