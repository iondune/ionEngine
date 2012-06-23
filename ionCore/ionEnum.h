#ifndef _ION_ENUM_H_INCLUDED_
#define _ION_ENUM_H_INCLUDED_


template <typename Domain>
class EnumImplementation
{

protected:

	typedef typename Domain::Domain Element;
	typedef EnumImplementation<Domain> Other;
	Element Value;

public:

	EnumImplementation(Element const value)
		: Value(value)
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

template <typename Domain>
class Enum : public Domain, public EnumImplementation<Domain>
{

public:

	Enum(Element const value)
		: EnumImplementation(value)
	{}

};

#endif
