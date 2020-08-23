
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

		class FileOutput : public Output
		{

		public:

			FileOutput(std::string const & FileName);
			~FileOutput();
			virtual void Write(ELogChannel const Channel, string const & Message);

		private:

			std::ofstream * File = nullptr;

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
#ifndef ION_CONFIG_SUPPRESS_LOG
			WriteInternal(Channel, tfm::format(Format, args...));
#endif
		}

		static void AddOutput(ELogChannel const Which, Output * Out);
		static void AddOutputToAllChannels(Output * Out);
		static void AddDefaultOutputs();

	protected:

		class Channel
		{

		public:

			ELogChannel const Which;
			string Label;
			vector<Output *> WriteTo;

			Channel(ELogChannel const Which, string const & Label);

			void WriteMessage(string const & ToWrite);

		};

		static Channel & GetChannel(ELogChannel const Which);
		static string GetChannelLabel(ELogChannel const Which);

		static void WriteInternal(ELogChannel const Which, std::string const & Message);

	};

}
