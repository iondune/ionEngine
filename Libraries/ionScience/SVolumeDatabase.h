
#pragma once

#include "SVolume.h"
#include "IDatabase.h"
#include "IDataRecord.h"


namespace ion
{

	template <typename T>
	struct SVolumeDatabase;

	template <typename T>
	struct SVolumeDataRecord : public IDataRecord<T>
	{

		SVolumeDataRecord();
		SVolumeDataRecord(SVolumeDatabase<T> & database);
		SVolumeDataRecord<T> & operator = (SVolumeDataRecord<T> const & other);

		T GetField(std::string const & Field) const;
		T & GetField(std::string const & Field);

		std::vector<T> Values;
		SVolumeDatabase<T> * Database;

	};

	template <typename T>
	struct SVolumeDatabase : public IDatabase<T>, public SVolume<SVolumeDataRecord<T>>
	{

		using SVolume<SVolumeDataRecord<T>>::Values;
		using SVolume<SVolumeDataRecord<T>>::Dimensions;
		using SVolume<SVolumeDataRecord<T>>::Get;

		SVolumeDatabase()
			: SVolume<SVolumeDataRecord<T>>(SVolumeDataRecord<T>(* this))
		{}

		void Allocate()
		{
			Values.resize(Dimensions.X * Dimensions.Y * Dimensions.Z, SVolumeDataRecord<T>(* this));
		}

		void AddField(std::string const & Field)
		{
			if (HasField(Field))
				return;

			Fields.push_back(Field);

			for (auto it = Values.begin(); it != Values.end(); ++ it)
				it->Values.resize(Fields.size());
		}

		bool HasField(std::string const & Field)
		{
			auto it = std::find(Fields.begin(), Fields.end(), Field);
			return it != Fields.end();
		}

		SRange<T> GetFieldRange(std::string const & Field, T const OutlierCutoff = 5, SRange<T> const & acceptedValues = SRange<T>::Full) const
		{
			// Calculate mean
			T Mean = 0;
			size_t Count = Values.size();
			for (auto it = Values.begin(); it != Values.end(); ++ it)
			{
				T const v = it->GetField(Field);
				if (! acceptedValues.Contains(v) || v != v)
					Count --;
				else
					Mean += v;
			}
			Mean /= Count;

			// Calculate standard absolute value deviation
			T StdDeviation = 0;
			for (auto it = Values.begin(); it != Values.end(); ++ it)
			{
				double const v = it->GetField(Field);
				if (acceptedValues.Contains(v) && v == v)
					StdDeviation += abs(v - Mean);
			}
			StdDeviation /= Count - 1;

			// Find min/max
			T Min = std::numeric_limits<T>::max(), Max = -std::numeric_limits<T>::max();
			for (auto it = Values.begin(); it != Values.end(); ++ it)
			{
				T const v = it->GetField(Field);
				if (v < Mean + OutlierCutoff * StdDeviation && v > Mean - OutlierCutoff * StdDeviation)
				{
					if (v > Max)
						Max = v;
					if (v < Min)
						Min = v;
				}
			}

			return SRange<T>(Min, Max);
		}

		void WriteToFile(std::ofstream & File)
		{
			// Write Dimensions
			File.write((char *) & Dimensions.X, sizeof(uint));
			File.write((char *) & Dimensions.Y, sizeof(uint));
			File.write((char *) & Dimensions.Z, sizeof(uint));

			// Write Fields
			size_t const FieldCount = Fields.size();
			File.write((char *) & FieldCount, sizeof(size_t));
			for (auto it = Fields.begin(); it != Fields.end(); ++ it)
			{
				size_t const Length = it->size();
				File.write((char *) & Length, sizeof(size_t));
				File.write(it->c_str(), Length);
			}

			// Write Records
			size_t const RecordCount = Values.size();
			File.write((char *) & RecordCount, sizeof(size_t));

			for (auto it = Values.begin(); it != Values.end(); ++ it)
				File.write((char *) & it->Values.begin(), sizeof(T));
		}

		void ReadFromFile(std::ifstream & File)
		{
			Values.clear();
			Fields.clear();

			// Read Dimensions
			File.read((char *) & Dimensions.X, sizeof(uint));
			File.read((char *) & Dimensions.Y, sizeof(uint));
			File.read((char *) & Dimensions.Z, sizeof(uint));

			// Read Fields
			size_t FieldCount;
			File.read((char *) & FieldCount, sizeof(size_t));

			for (size_t i = 0; i < FieldCount; ++ i)
			{
				size_t Length;
				File.read((char *) & Length, sizeof(size_t));

				char * Buffer = new char[Length + 1];
				File.read(Buffer, Length);
				Buffer[Length] = '\0';

				Fields.push_back(Buffer);
				delete[] Buffer;
			}

			// Read Records
			size_t RecordCount;
			File.read((char *) & RecordCount, sizeof(size_t));
			Values.reserve(RecordCount);

			for (size_t i = 0; i < RecordCount; ++ i)
			{
				SVolumeDataRecord<T> Record(* this);
				for (size_t t = 0; t < FieldCount; ++ t)
				{
					T Value;
					File.read((char *) & Value, sizeof(T));
					Record.Values.push_back(Value);
				}

				Values.push_back(Record);
			}
		}

		std::vector<std::string> Fields;

	};

	template <typename T>
	SVolumeDataRecord<T>::SVolumeDataRecord()
		: Database()
	{}

	template <typename T>
	SVolumeDataRecord<T>::SVolumeDataRecord(SVolumeDatabase<T> & database)
		: Database(& database)
	{
		Values.resize(Database->Fields.size(), 0);
	}

	template <typename T>
	SVolumeDataRecord<T> & SVolumeDataRecord<T>::operator = (SVolumeDataRecord<T> const & other)
	{
		if (!Database)
		{
			Database = other.Database;
			Values.resize(Database->Fields.size(), 0);
		}

		assert(Database == other.Database);
		Values = other.Values;

		return * this;
	}

	template <typename T>
	T SVolumeDataRecord<T>::GetField(std::string const & Field) const
	{
		if (!Database->HasField(Field))
			return 0;

		auto it = std::find(Database->Fields.begin(), Database->Fields.end(), Field);
		assert(it != Database->Fields.end());

		return Values[std::distance(Database->Fields.begin(), it)];
	}

	template <typename T>
	T & SVolumeDataRecord<T>::GetField(std::string const & Field)
	{
		Database->AddField(Field);

		auto it = std::find(Database->Fields.begin(), Database->Fields.end(), Field);
		assert(it != Database->Fields.end());

		return Values[std::distance(Database->Fields.begin(), it)];
	}

}
