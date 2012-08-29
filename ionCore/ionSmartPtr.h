#ifndef _IONSMARTPTR_H_INCLUDED_
#define _IONSMARTPTR_H_INCLUDED_

#include <boost/shared_ptr.hpp>

template <typename T>
class smartPtr
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

	virtual T * const operator -> ()
	{
		return * shared_ptr;
	}

	virtual T * const operator * ()
	{
		return * shared_ptr;
	}

	virtual T const * const operator -> () const
	{
		return * shared_ptr;
	}

	virtual T const * const operator * () const
	{
		return * shared_ptr;
	}

	virtual void set(T * const ptr)
	{
		shared_ptr.reset(ptr);
	}

	virtual void reset(T * const ptr)
	{
		shared_ptr.reset(ptr);
	}

	virtual void reset()
	{
		shared_ptr.reset();
	}

	virtual void clear()
	{
		shared_ptr.reset();
	}

};

template <typename T>
class staticPtr : public smartPtr
{

private:

	T * static_ptr;

public:

	staticPtr()
		: static_ptr(0)
	{}

	staticPtr(T * const ptr)
		: static_ptr(ptr)
	{}

	staticPtr(smartPtr const & other)
		: static_ptr(other.static_ptr)
	{}

	staticPtr & operator = (staticPtr const & other)
	{
		static_ptr = other.static_ptr;
	}

	virtual T * const operator -> ()
	{
		return static_ptr;
	}

	virtual T * const operator * ()
	{
		return static_ptr;
	}

	virtual T const * const operator -> () const
	{
		return * static_ptr;
	}

	virtual T const * const operator * () const
	{
		return * static_ptr;
	}

	virtual void set(T * const ptr)
	{
		static_ptr = ptr;
	}

	virtual void reset(T * const ptr)
	{
		static_ptr = ptr;
	}

	virtual void reset()
	{
		static_ptr = 0;
	}

	virtual void clear()
	{
		static_ptr = 0;
	}

};

#endif
