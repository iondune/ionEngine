
/*!
\file ionLogger.h
\ingroup ionCore
\brief Logging class
*/


#pragma once

#include "ionTypes.h"
#include "String.h"


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

			virtual void Write(ELogChannel const Channel, string const & Message) = 0;

		};

		class StandardOutput : public Output
		{

		public:

			StandardOutput(std::ostream & Stream);
			virtual void Write(ELogChannel const Channel, string const & Message);

		private:

			std::ostream & Stream;

		};

		class WindowsLogOutput : public Output
		{

		public:

			virtual void Write(ELogChannel const Channel, string const & Message);

		};

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

		static vector<string> const & GetMessages();
		static vector<string> const & GetMessages(ELogChannel const Which);
		static vector<pair<string, int>> const & GetMessagesDetail(ELogChannel const Which);

		static void AddOutput(ELogChannel const Which, Output * Out);
		static void AddOutputToAllChannels(Output * Out);
		static void AddDefaultOutputs();

		static void Clear();

	protected:

		class Channel
		{

		public:

			ELogChannel const Which;
			string Label;
			vector<Output *> WriteTo;
			vector<string> Messages;
			vector<pair<string, int>> MessagesDetail;
			unordered_map<string, int> MessageMap;

			Channel(ELogChannel const Which, string const & Label);

			//! \return true if this is a new message, false if not
			bool WriteMessage(string const & ToWrite);

			vector<pair<string, int>> const & GetMessagesDetail();

		};

		static Channel & GetChannel(ELogChannel const Which);
		static string GetChannelLabel(ELogChannel const Which);

		static void WriteInternal(ELogChannel const Which, std::string const & Message);
		static vector<string> & AllLoggedMessages();

	};

}
