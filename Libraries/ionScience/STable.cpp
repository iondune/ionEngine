
#include "STable.h"


namespace ion
{

	std::vector<STable::SRow> const & STable::GetValues() const
	{
		return Rows;
	}

	std::vector<STable::SRow> const & STable::GetRows() const
	{
		return Rows;
	}

	STable::SRow & STable::AddRow()
	{
		Rows.push_back(SRow(* this, Rows.size()));

		for (auto it = Fields.begin(); it != Fields.end(); ++ it)
			it->second.resize(Maximum(Rows.size(), it->second.size()), 0);

		return Rows.back();
	}

	void STable::AddField(std::string const & Field)
	{
		Fields[Field].resize(Rows.size());
	}

	bool STable::HasField(std::string const & Field)
	{
		return Fields.find(Field) != Fields.end();
	}

	SRange<double> STable::GetFieldRange(std::string const & Field, double const OutlierCutoff, SRange<double> const & acceptedValues) const
	{
		// Calculate mean
		double Mean = 0;
		size_t Count = Rows.size();
		for (auto it = Rows.begin(); it != Rows.end(); ++ it)
		{
			double const v = it->GetField(Field);
			if (! acceptedValues.Contains(v) || v != v)
				Count --;
			else
				Mean += it->GetField(Field);
		}
		Mean /= (double) (Count);

		// Calculate standard absolute value deviation
		double StdDeviation = 0;
		for (auto it = Rows.begin(); it != Rows.end(); ++ it)
		{
			double const v = it->GetField(Field);
			if (acceptedValues.Contains(v) && v == v)
				StdDeviation += Abs(v - Mean);
		}
		StdDeviation /= (double) (Count - 1);

		// Find min/max
		double Min = std::numeric_limits<double>::max(), Max = -std::numeric_limits<double>::max();
		for (auto it = Rows.begin(); it != Rows.end(); ++ it)
		{
			double const v = it->GetField(Field);
			if (v < Mean + OutlierCutoff * StdDeviation && v > Mean - OutlierCutoff * StdDeviation)
			{
				if (v > Max)
					Max = v;
				if (v < Min)
					Min = v;
			}
		}

		return SRange<double>(Min, Max);
	}

	STable::SFieldIterator STable::Begin(std::string const & Field)
	{
		return SFieldIterator(Rows.begin(), Field);
	}

	STable::SFieldIterator STable::End(std::string const & Field)
	{
		return SFieldIterator(Rows.end(), Field);
	}

	vector<STable::SRow>::iterator STable::begin()
	{
		return Rows.begin();
	}

	vector<STable::SRow>::iterator STable::end()
	{
		return Rows.end();
	}

	size_t STable::Size() const
	{
		return Rows.size();
	}

	void STable::Clear()
	{
		Rows.clear();
	}

	void STable::WriteToFile(std::ofstream & File)
	{
		// Write Fields
		size_t Dims = Fields.size();
		File.write((char *) & Dims, sizeof(size_t));

		for (auto it = Fields.begin(); it != Fields.end(); ++ it)
		{
			// Write Label
			Dims = it->first.size();
			File.write((char *) & Dims, sizeof(size_t));
			File.write(it->first.c_str(), Dims);

			// Write Data
			Dims = it->second.size();
			File.write((char *) & Dims, sizeof(size_t));
			File.write((char *) & it->second.front(), Dims * sizeof(double));
		}

		// Write Values
		Dims = Rows.size();
		File.write((char *) & Dims, sizeof(size_t));

		for (auto it = Rows.begin(); it != Rows.end(); ++ it)
			File.write((char *) & it->Index, sizeof(size_t));
	}

	void STable::ReadFromFile(std::ifstream & File)
	{
		Rows.clear();

		size_t FieldCount;
		File.read((char *) & FieldCount, sizeof(size_t));

		for (size_t i = 0; i < FieldCount; ++ i)
		{
			// Read Label
			size_t LabelLength;
			File.read((char *) & LabelLength, sizeof(size_t));
			char * Buffer = new char[LabelLength + 1];
			File.read(Buffer, LabelLength);
			Buffer[LabelLength] = '\0';

			// Read Data
			size_t DataLength;
			File.read((char *) & DataLength, sizeof(size_t));
			double * DataBuffer = new double[DataLength];
			File.read((char *) DataBuffer, DataLength * sizeof(double));
			Fields[Buffer].reserve(DataLength);
			for (size_t t = 0; t < DataLength; ++ t)
				Fields[Buffer].push_back(DataBuffer[t]);

			delete[] Buffer;
			delete[] DataBuffer;
		}

		// Read Values
		size_t ValueCount;
		File.read((char *) & ValueCount, sizeof(size_t));
		Rows.reserve(ValueCount);

		for (size_t i = 0; i < ValueCount; ++ i)
		{
			size_t InternalIndex;
			File.read((char *) & InternalIndex, sizeof(size_t));
			assert(InternalIndex == Rows.size());

			Rows.push_back(SRow(* this, Rows.size()));

			for (auto it = Fields.begin(); it != Fields.end(); ++ it)
				it->second.resize(Maximum(Rows.size(), it->second.size()), 0);
		}
	}

}
