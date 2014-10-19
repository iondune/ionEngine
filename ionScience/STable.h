
#pragma once

#include <ionCore.h>
#include <ionMath.h>

#include "SRange.h"
#include "IDataRecord.h"
#include "IDatabase.h"


class STable : public IDatabase<f64>
{

public:

	class SRow : public IDataRecord<f64>
	{

		friend class STable;

	public:

		f64 GetField(std::string const & Field) const;
		f64 & GetField(std::string const & Field);

		SRow operator = (SRow const & Other);

	protected:
		
		SRow(STable & table, u64 const index);

		u64 Index;
		STable & Table;

	};

	class SFieldIterator
	{

	public:

		typedef std::vector<SRow>::iterator::iterator_category iterator_category;
		typedef f64 value_type;
		typedef std::vector<SRow>::iterator::difference_type difference_type;
		typedef f64 * pointer;
		typedef f64 & reference;

		SFieldIterator(std::vector<SRow>::iterator iterator, std::string const & field);

		SFieldIterator & operator ++ ();
		SFieldIterator operator ++ (int);

		f64 operator * () const;
		f64 & operator * ();
		f64 const * operator -> () const;
		f64 * operator -> ();

		bool operator < (SFieldIterator const & other) const;
		bool operator != (SFieldIterator const & other) const;

	protected:

		std::vector<SRow>::iterator Iterator;
		std::string Field;

	};

	std::vector<SRow> const & GetValues() const;
	std::vector<SRow> const & GetRows() const;

	SRow & AddRow();
	void AddField(std::string const & Field);
	bool HasField(std::string const & Field);

	//! \param OutlierCutoff Values outside of this many standard deviations are excluded
	SRange<f64> GetFieldRange(std::string const & Field, double const OutlierCutoff = 5, SRange<f64> const & acceptedValues = SRange<f64>::Full) const;

	SFieldIterator Begin(std::string const & Field);
	SFieldIterator End(std::string const & Field);

	u64 Size() const;
	void Clear();
	void WriteToFile(std::ofstream & File);
	void ReadFromFile(std::ifstream & File);

protected:

	std::vector<SRow> Rows;
	std::map<std::string, std::vector<double> > Fields;

};

template <class Iterator>
Iterator MaximumRealElement(Iterator First, Iterator Last)
{
	Iterator Found = First;
	if (First != Last)
		for (; ++ First != Last; )
			if (*Found != *Found || (*Found < *First && *First == *First))
				Found = First;
	return Found;
}

template <class Iterator>
Iterator MinimumRealElement(Iterator First, Iterator Last)
{
	Iterator Found = First;
	if (First != Last)
		for (; ++ First != Last; )
			if (*Found != *Found || (*First < *Found && *First == *First))
				Found = First;
	return Found;
}
