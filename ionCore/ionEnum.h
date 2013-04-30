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

	ION_FUNC_DEF EnumImplementation(Element const value)
		: Value(value)
	{}

	ION_FUNC_DEF EnumImplementation(int const value)
		: Value((Element) value)
	{}

	ION_FUNC_DEF Element const getValue() const
	{
		return Value;
	}

	ION_FUNC_DEF operator Element const() const
	{
		return Value;
	}

	ION_FUNC_DEF bool const operator == (Element const & v)
	{
		return Value == v;
	}

	ION_FUNC_DEF bool const operator == (Other const & v)
	{
		return Value == v.Value;
	}

	ION_FUNC_DEF bool const operator != (Element const & v)
	{
		return Value != v;
	}

	ION_FUNC_DEF bool const operator != (Other const & v)
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

	ION_FUNC_DEF Enum(Value const value)
		: EnumImplementation<TDomain>(value)
	{}

	ION_FUNC_DEF Enum(int const value)
		: EnumImplementation<TDomain>(value)
	{}

};

#endif
