
#pragma once

#include <ionCore.h>


template <typename Parameter>
class ICallable
{

public:

	virtual void operator () (Parameter & p) = 0;

};

template <typename Class, typename Parameter>
class CMemberFunctionCallable
{

public:

	void operator () (Parameter & p)
	{
		(Object->* MemberFunction)(p);
	}

	CMemberFunctionCallable(Class * object, void (Class::* memberFunction)(Parameter &))
		: Object(object), MemberFunction(memberFunction)
	{}

protected:

	void (Class::* MemberFunction)(Parameter &);
	Class * Object;

};

template <typename Class, typename Parameter>
sharedPtr<CMemberFunctionCallable<Class, Parameter>> BindMemberFunction(Class * Object, void (Class::* MemberFunction)(Parameter &))
{
	return new CMemberFunctionCallable<Class, Parameter>{Object, MemberFunction};
}
