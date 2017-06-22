
#pragma once


namespace ion
{

	template <typename T>
	class IDataRecord
	{

	public:

		virtual T GetField(std::string const & Field) const = 0;
		virtual T & GetField(std::string const & Field) = 0;

	};

}
