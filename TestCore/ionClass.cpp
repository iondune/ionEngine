
#include "catch.hpp"
#include <ionCore.h>


class A
{};

class B : public A
{};

class C
{
public:
	virtual ~C()
	{}
};

TEST_CASE("InstanceOf", "[ionClass :: InstanceOf]")
{
	A a;
	B b;
	C c;
	
	REQUIRE(InstanceOf<A>(a));
	REQUIRE(InstanceOf<A>(&a));
	REQUIRE(InstanceOf<A>(b));
	REQUIRE(InstanceOf<A>(&b));
	REQUIRE(! InstanceOf<A>(c));
	REQUIRE(! InstanceOf<A>(&c));
	REQUIRE(NULL != As<A>(&a));
	REQUIRE(NULL != As<A>(&b));
	REQUIRE(NULL == As<A>(&c));
}

TEST_CASE("Type", "[ionClass :: Type]")
{
	Type TypeA(typeid(A));
	Type TypeB(typeid(B));
	Type TypeC(typeid(C));
	
	REQUIRE((TypeA < TypeB) != (TypeB < TypeA));
	REQUIRE((TypeA < TypeC) != (TypeC < TypeA));
	REQUIRE((TypeB < TypeC) != (TypeC < TypeB));
}

class F;

class E : public Singleton<E>
{
public:
	SingletonPointer<F> FPtr;
};

class F : public Singleton<F>
{
public:
	SingletonPointer<E> EPtr;
};

TEST_CASE("Singleton lazy initialization", "[ionClass :: Singleton]")
{
	SingletonPointer<E> e;
	SingletonPointer<F> f;
	
	REQUIRE(e->FPtr.Get() == f.Get());
	REQUIRE(f->EPtr.Get() == e.Get());
}
