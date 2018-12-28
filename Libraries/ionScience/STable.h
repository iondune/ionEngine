
#pragma once

#include <ionCore.h>
#include <ionMath.h>

#include "SRange.h"
#include "IDataRecord.h"
#include "IDatabase.h"


namespace ion
{

	class STable : public IDatabase<double>
	{

	public:

		class SRow : public IDataRecord<double>
		{

			friend class STable;

		public:

			double GetField(std::string const & Field) const;
			double & GetField(std::string const & Field);

			SRow operator = (SRow const & Other);

		protected:

			SRow(STable & table, size_t const index);

			size_t Index;
			STable & Table;

		};

		class SFieldIterator
		{

		public:

			typedef std::vector<SRow>::iterator::iterator_category iterator_category;
			typedef double value_type;
			typedef std::vector<SRow>::iterator::difference_type difference_type;
			typedef double * pointer;
			typedef double & reference;

			SFieldIterator(std::vector<SRow>::iterator iterator, std::string const & field);

			SFieldIterator & operator ++ ();
			SFieldIterator operator ++ (int);

			double operator * () const;
			double & operator * ();
			double const * operator -> () const;
			double * operator -> ();

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
		//! \param Field Field to find range of
		//! \param acceptedValues Range of values to consider (superset of return value)
		SRange<double> GetFieldRange(std::string const & Field, double const OutlierCutoff = 5, SRange<double> const & acceptedValues = SRange<double>::Full) const;

		SFieldIterator Begin(std::string const & Field);
		SFieldIterator End(std::string const & Field);

		vector<SRow>::iterator begin();
		vector<SRow>::iterator end();

		size_t Size() const;
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

}
