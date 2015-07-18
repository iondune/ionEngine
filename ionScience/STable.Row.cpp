#include "STable.h"


f64 STable::SRow::GetField(std::string const & Field) const
{
	std::map<std::string, std::vector<double> >::const_iterator it;
	if ((it = Table.Fields.find(Field)) == Table.Fields.end())
		return 0;

	return it->second[Index];
}

f64 & STable::SRow::GetField(std::string const & Field)
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

STable::SRow::SRow(STable & table, u64 const index)
	: Table(table), Index(index)
{}
