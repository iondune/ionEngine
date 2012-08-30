#ifndef _IONSMARTPTR_H_INCLUDED_
#define _IONSMARTPTR_H_INCLUDED_

#include <boost/shared_ptr.hpp>

template <typename T>
class smartPtr
{

protected:

	boost::shared_ptr<T> shared_ptr;

public:

	smartPtr()
	{}

	smartPtr(T * const ptr)
		: shared_ptr(ptr)
	{}

	smartPtr(smartPtr<T> const & other)
		: shared_ptr(other.shared_ptr)
	{}

	template <typename U>
	smartPtr(smartPtr<U> const & other)
		: shared_ptr(other.getImplementation())
	{}

	smartPtr<T> & operator = (smartPtr<T> const & other)
	{
		shared_ptr = other.shared_ptr;
	}
	
	template <typename U>
	smartPtr<T> & operator = (smartPtr<U> const & other)
	{
		shared_ptr = other.getImplementation();
	}

	virtual T * const operator -> ()
	{
		return shared_ptr.get();
	}

	virtual T * const operator * ()
	{
		return shared_ptr.get();
	}

	virtual T const * const operator -> () const
	{
		return shared_ptr.get();
	}

	virtual T const * const operator * () const
	{
		return shared_ptr.get();
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

	virtual bool const operator ! ()
	{
		return ! ** this;
	}

	virtual boost::shared_ptr<T> const & getImplementation() const
	{
		return shared_ptr;
	}

};

template <typename T>
static smartPtr<T> smartNew(T * t)
{
	return smartPtr<T>(t);
}

template <typename T>
class staticPtr : public smartPtr<T>
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
		return static_ptr;
	}

	virtual T const * const operator * () const
	{
		return static_ptr;
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
