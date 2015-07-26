
#include <ionCore.h>
#include <catch.hpp>


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

	A const * const aPtr = &a;

	REQUIRE(InstanceOf<A>(a));
	REQUIRE(InstanceOf<A>(aPtr));
	REQUIRE(InstanceOf<A>(&a));
	REQUIRE(InstanceOf<A>(b));
	REQUIRE(InstanceOf<A>(&b));
	REQUIRE(InstanceOf<C>(c));
	REQUIRE(! InstanceOf<A>(c));
	REQUIRE(! InstanceOf<A>(&c));
	REQUIRE(nullptr != As<A>(&a));
	REQUIRE(nullptr != As<A>(&b));
	REQUIRE(nullptr == As<A>(&c));
}

class Base
{
public:
	Base() {}
	virtual ~Base() {}
};

class Derived : public Base
{};

TEST_CASE("ionClass::As", "As function converts between objects")
{
	Base a;
	Base const constA;
	Derived b;
	C c;

	Base const * const aPtr = &a;
	Derived const * const bPtr = &b;
	C const * const cPtr = &c;

	REQUIRE(As<Derived>((Base*)&b) == &b);
	REQUIRE(As<Derived>((Base const * const)bPtr) == bPtr);
	REQUIRE(As<Base>(& a) == & a);
	REQUIRE(! As<Derived>(& a));
	REQUIRE(! & As<Derived>(a));
	REQUIRE(! & As<Derived>(constA));
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
	SingletonPointer<E> const constE = SingletonPointer<E>();
	SingletonPointer<F> f;

	REQUIRE(e->FPtr.Get() == f.Get());
	REQUIRE(constE->FPtr.Get() == f.Get());
	REQUIRE(f->EPtr.Get() == e.Get());
	REQUIRE(f->EPtr.Get() == constE.Get());
	REQUIRE(f->EPtr == e);
	REQUIRE(f->EPtr == constE);
}
