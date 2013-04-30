#ifndef _ION_ENUM_H_INCLUDED_
#define _ION_ENUM_H_INCLUDED_

#include "ionConfig.h"


template <typename TDomain>
class EnumImplementation
{

protected:

	typedef typename TDomain::Domain Element;
	typedef EnumImplementation<TDomain> Other;
	Element Value;

public:

	EnumImplementation(Element const value)
		: Value(value)
	{}

	EnumImplementation(int const value)
		: Value((Element) value)
	{}

	Element const getValue() const
	{
		return Value;
	}

	operator Element const() const
	{
		return Value;
	}

	bool const operator == (Element const & v)
	{
		return Value == v;
	}

	bool const operator == (Other const & v)
	{
		return Value == v.Value;
	}

	bool const operator != (Element const & v)
	{
		return Value != v;
	}

	bool const operator != (Other const & v)
	{
		return Value != v.Value;
	}

};

template <typename TDomain>
class Enum : public TDomain, public EnumImplementation<TDomain>
{

protected:

	typedef typename EnumImplementation<TDomain>::Element Value;

public:

	Enum(Value const value)
		: EnumImplementation<TDomain>(value)
	{}

	Enum(int const value)
		: EnumImplementation<TDomain>(value)
	{}

};

#endif
