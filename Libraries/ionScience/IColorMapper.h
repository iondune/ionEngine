
#pragma once

#include <ionScene.h>
#include <ionCore.h>

#include "IDataRecord.h"
#include "IDatabase.h"


namespace ion
{

	class IColorMapper
	{

	public:

		virtual color4f const GetColor(IDataRecord<double> const & DataRecord) = 0;
		virtual void PreProcessValues(IDatabase<double> & Database) = 0;

	};

}
