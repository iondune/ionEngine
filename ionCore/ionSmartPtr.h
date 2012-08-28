#ifndef _IONSMARTPTR_H_INCLUDED_
#define _IONSMARTPTR_H_INCLUDED_

#include <boost/shared_ptr.hpp>

template <class T>
struct smartPtr
{

private:

	boost::shared_ptr<T> shared_ptr;

public:

	smartPtr()
	{}

	smartPtr(T * const ptr)
		: shared_ptr(ptr)
	{}

	smartPtr(smartPtr const & other)
		: shared_ptr(other.shared_ptr)
	{}

	smartPtr & operator = (smartPtr const & other)
	{
		shared_ptr = other.shared_ptr;
	}

	T * const operator -> ()
	{
		return * shared_ptr;
	}

	T * const operator * ()
	{
		return * shared_ptr;
	}

	void set(T * const ptr)
	{
		shared_ptr.reset(ptr);
	}

	void reset(T * const ptr)
	{
		shared_ptr.reset(ptr);
	}

	void reset()
	{
		shared_ptr.reset();
	}

	void clear()
	{
		shared_ptr.reset();
	}

};

#endif
