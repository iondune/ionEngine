
#pragma once

#include <GL/glew.h>

#include "SVolume.h"
#include "IDatabase.h"
#include "IDataRecord.h"


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

	void MakeOpenGLVolume(u32 const VolumeHandle, IColorMapper * ColorMapper)
	{
		ColorMapper->PreProcessValues(* this);

		u8 * const VolumeData = new u8[Dimensions.X * Dimensions.Y * Dimensions.Z * 4];

		for (s32 k = 0; k < Dimensions.Z; ++ k)
		for (s32 j = 0; j < Dimensions.Y; ++ j)
		for (s32 i = 0; i < Dimensions.X; ++ i)
		{
			u32 const Index = i + j * Dimensions.X + k * Dimensions.X * Dimensions.Y;
			color4i const Color = ColorMapper->GetColor(Get(i, j, k));

			for (u32 t = 0; t < 4; ++ t)
				VolumeData[Index * 4 + t] = Color[t];
		}

		glBindTexture(GL_TEXTURE_3D, VolumeHandle);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, Dimensions.X, Dimensions.Y, Dimensions.Z, 0, GL_RGBA, GL_UNSIGNED_BYTE, VolumeData);
		glBindTexture(GL_TEXTURE_3D, 0);
	}

	void WriteToFile(std::ofstream & File)
	{
		// Write Dimensions
		File.write((char *) & Dimensions.X, sizeof(u32));
		File.write((char *) & Dimensions.Y, sizeof(u32));
		File.write((char *) & Dimensions.Z, sizeof(u32));

		// Write Fields
		u32 const FieldCount = Fields.size();
		File.write((char *) & FieldCount, sizeof(u32));
		for (auto it = Fields.begin(); it != Fields.end(); ++ it)
		{
			u32 const Length = it->size();
			File.write((char *) & Length, sizeof(u32));
			File.write(it->c_str(), Length);
		}

		// Write Records
		u32 const RecordCount = Values.size();
		File.write((char *) & RecordCount, sizeof(u32));

		for (auto it = Values.begin(); it != Values.end(); ++ it)
			File.write((char *) & it->Values.begin(), sizeof(T));
	}

	void ReadFromFile(std::ifstream & File)
	{
		Values.clear();
		Fields.clear();

		// Read Dimensions
		File.read((char *) & Dimensions.X, sizeof(u32));
		File.read((char *) & Dimensions.Y, sizeof(u32));
		File.read((char *) & Dimensions.Z, sizeof(u32));

		// Read Fields
		u32 FieldCount;
		File.read((char *) & FieldCount, sizeof(u32));

		for (u32 i = 0; i < FieldCount; ++ i)
		{
			u32 Length;
			File.read((char *) & Length, sizeof(u32));

			char * Buffer = new char[Length + 1];
			File.read(Buffer, Length);
			Buffer[Length] = '\0';

			Fields.push_back(Buffer);
			delete [] Buffer;
		}

		// Read Records
		u32 RecordCount;
		File.read((char *) & RecordCount, sizeof(u32));
		Values.reserve(RecordCount);

		for (u32 i = 0; i < RecordCount; ++ i)
		{
			SVolumeDataRecord<T> Record(* this);
			for (u32 t = 0; t < FieldCount; ++ t)
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
