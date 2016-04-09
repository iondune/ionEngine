
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

TEST_CASE("InstanceOf", "")
{
	A a;
	B b;
	C c;

	A const * const aPtr = &a;

	CHECK(InstanceOf<A>(a));
	CHECK(InstanceOf<A>(aPtr));
	CHECK(InstanceOf<A>(&a));
	CHECK(InstanceOf<A>(b));
	CHECK(InstanceOf<A>(&b));
	CHECK(InstanceOf<C>(c));
	CHECK(! InstanceOf<A>(c));
	CHECK(! InstanceOf<A>(&c));
	CHECK(nullptr != As<A>(&a));
	CHECK(nullptr != As<A>(&b));
	CHECK(nullptr == As<A>(&c));
}

class TestBase
{
public:
	TestBase() {}
	virtual ~TestBase() {}
};

class TestDerived : public TestBase
{};

TEST_CASE("ionClass::As", "As function converts between objects")
{
	TestBase a;
	TestBase const constA;
	TestDerived b;
	C c;

	TestBase const * const aPtr = &a;
	TestDerived const * const bPtr = &b;
	C const * const cPtr = &c;

	CHECK(As<TestDerived>((TestBase*)&b) == &b);
	CHECK(As<TestDerived>((TestBase const * const)bPtr) == bPtr);
	CHECK(As<TestBase>(& a) == & a);
	CHECK(! As<TestDerived>(& a));
	CHECK(! & As<TestDerived>(a));
	CHECK(! & As<TestDerived>(constA));
}

TEST_CASE("Type", "[ionClass :: Type]")
{
	Type TypeA(typeid(A));
	Type TypeB(typeid(B));
	Type TypeC(typeid(C));

	CHECK((TypeA < TypeB) != (TypeB < TypeA));
	CHECK((TypeA < TypeC) != (TypeC < TypeA));
	CHECK((TypeB < TypeC) != (TypeC < TypeB));
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

	CHECK(e->FPtr.Get() == f.Get());
	CHECK(constE->FPtr.Get() == f.Get());
	CHECK(f->EPtr.Get() == e.Get());
	CHECK(f->EPtr.Get() == constE.Get());
	CHECK(f->EPtr == e);
	CHECK(f->EPtr == constE);
}

