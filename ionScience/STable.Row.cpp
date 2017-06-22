
#include "STable.h"


namespace ion
{

	double STable::SRow::GetField(std::string const & Field) const
	{
		std::map<std::string, std::vector<double> >::const_iterator it;
		if ((it = Table.Fields.find(Field)) == Table.Fields.end())
			return 0;

		return it->second[Index];
	}

	double & STable::SRow::GetField(std::string const & Field)
	{
		if (! Table.HasField(Field))
			Table.AddField(Field);
		std::map<std::string, std::vector<double> >::iterator it;
		assert((it = Table.Fields.find(Field)) != Table.Fields.end());

		return it->second[Index];
	}

	STable::SRow STable::SRow::operator = (SRow const & Other)
	{
		assert(& Other.Table == & Table);
		Index = Other.Index;

		return * this;
	}

	STable::SRow::SRow(STable & table, size_t const index)
		: Table(table), Index(index)
	{}

}
