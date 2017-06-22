
#include "STable.h"


namespace ion
{

	STable::SFieldIterator::SFieldIterator(std::vector<SRow>::iterator iterator, std::string const & field)
		: Iterator(iterator), Field(field)
	{}

	STable::SFieldIterator & STable::SFieldIterator::operator ++ ()
	{
		++ Iterator;
		return * this;
	}

	STable::SFieldIterator STable::SFieldIterator::operator ++ (int)
	{
		SFieldIterator temp = * this;
		++ Iterator;
		return temp;
	}

	double STable::SFieldIterator::operator * () const
	{
		return Iterator->GetField(Field);
	}

	double & STable::SFieldIterator::operator * ()
	{
		return Iterator->GetField(Field);
	}

	double const * STable::SFieldIterator::operator -> () const
	{
		return & Iterator->GetField(Field);
	}

	double * STable::SFieldIterator::operator -> ()
	{
		return & Iterator->GetField(Field);
	}

	bool STable::SFieldIterator::operator < (SFieldIterator const & other) const
	{
		return Iterator < other.Iterator;
	}

	bool STable::SFieldIterator::operator != (SFieldIterator const & other) const
	{
		return Iterator != other.Iterator;
	}

}
