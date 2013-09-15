
#pragma once

#include <ionScene.h>
#include <ionCore.h>

#include "IDataRecord.h"
#include "IDatabase.h"


class IColorMapper
{

public:

	virtual SColorAf const GetColor(IDataRecord<f64> const & DataRecord) = 0;
	virtual void PreProcessValues(IDatabase<f64> & Database) = 0;

};
