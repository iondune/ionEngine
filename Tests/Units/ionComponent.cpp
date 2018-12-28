
#include <ionCore.h>
#include <catch.hpp>

using namespace ion;


class Component
{};

class AComponent : public Component
{
public:
	bool foo()
	{
		return true;
	}
};

class BComponent : public Component
{};

class CComponent : public AComponent
{};

TEST_CASE("IEntity::AddComponent")
{
	IEntity<Component> * Entity = new IEntity<Component>();
	AComponent * A = new AComponent();
	BComponent * B = new BComponent();
	CComponent * C = new CComponent();
	AComponent * A2 = new CComponent();

	CHECK(A == Entity->AddComponent(A));
	CHECK(A == Entity->AddComponent(A));
	CHECK(B == Entity->AddComponent(B));
	CHECK(C == Entity->AddComponent(C));
	CHECK(A2 == Entity->AddComponent(A2));
}

TEST_CASE("IEntity::GetComponentCount")
{
	IEntity<Component> * Entity = new IEntity<Component>();
	AComponent * A = new AComponent();
	BComponent * B = new BComponent();
	CComponent * C = new CComponent();
	AComponent * A2 = new CComponent();

	CHECK(Entity->GetComponentCount<AComponent>() == 0);
	CHECK(Entity->GetComponentCount<BComponent>() == 0);
	CHECK(Entity->GetComponentCount<CComponent>() == 0);
	Entity->AddComponent(A);
	CHECK(Entity->GetComponentCount<AComponent>() == 1);
	CHECK(Entity->GetComponentCount<BComponent>() == 0);
	CHECK(Entity->GetComponentCount<CComponent>() == 0);
	Entity->AddComponent(A);
	CHECK(Entity->GetComponentCount<AComponent>() == 2);
	CHECK(Entity->GetComponentCount<BComponent>() == 0);
	CHECK(Entity->GetComponentCount<CComponent>() == 0);
	Entity->AddComponent(B);
	CHECK(Entity->GetComponentCount<AComponent>() == 2);
	CHECK(Entity->GetComponentCount<BComponent>() == 1);
	CHECK(Entity->GetComponentCount<CComponent>() == 0);
	Entity->AddComponent(C);
	CHECK(Entity->GetComponentCount<AComponent>() == 2);
	CHECK(Entity->GetComponentCount<BComponent>() == 1);
	CHECK(Entity->GetComponentCount<CComponent>() == 1);
	Entity->AddComponent(A2);
	CHECK(Entity->GetComponentCount<AComponent>() == 3);
	CHECK(Entity->GetComponentCount<BComponent>() == 1);
	CHECK(Entity->GetComponentCount<CComponent>() == 1);
}

template <typename TComponent>
bool CheckRangeEquals(pair<typename std::multimap<Type, TComponent *>::iterator, typename std::multimap<Type, TComponent *>::iterator > const Iterators, std::initializer_list<TComponent *> const & List)
{
	auto it = Iterators.first;
	auto jt = List.begin();
	for (; it != Iterators.second && jt != List.end(); ++ it, ++ jt)
	{
		if (it->second != *jt)
			return false;
	}

	if (it != Iterators.second || jt != List.end())
		return false;

	return true;
}

TEST_CASE("IEntity::GetComponents")
{
	IEntity<Component> * Entity = new IEntity<Component>();
	AComponent * A = new AComponent();
	BComponent * B = new BComponent();
	CComponent * C = new CComponent();
	AComponent * A2 = new CComponent();

	CHECK(CheckRangeEquals<Component>(Entity->GetComponents<AComponent>(), {}));
	CHECK(CheckRangeEquals<Component>(Entity->GetComponents<BComponent>(), {}));
	CHECK(CheckRangeEquals<Component>(Entity->GetComponents<CComponent>(), {}));
	Entity->AddComponent(A);
	CHECK(CheckRangeEquals<Component>(Entity->GetComponents<AComponent>(), {A}));
	CHECK(CheckRangeEquals<Component>(Entity->GetComponents<BComponent>(), {}));
	CHECK(CheckRangeEquals<Component>(Entity->GetComponents<CComponent>(), {}));
	Entity->AddComponent(A);
	CHECK(CheckRangeEquals<Component>(Entity->GetComponents<AComponent>(), {A, A}));
	CHECK(CheckRangeEquals<Component>(Entity->GetComponents<BComponent>(), {}));
	CHECK(CheckRangeEquals<Component>(Entity->GetComponents<CComponent>(), {}));
	Entity->AddComponent(B);
	CHECK(CheckRangeEquals<Component>(Entity->GetComponents<AComponent>(), {A, A}));
	CHECK(CheckRangeEquals<Component>(Entity->GetComponents<BComponent>(), {B}));
	CHECK(CheckRangeEquals<Component>(Entity->GetComponents<CComponent>(), {}));
	Entity->AddComponent(C);
	CHECK(CheckRangeEquals<Component>(Entity->GetComponents<AComponent>(), {A, A}));
	CHECK(CheckRangeEquals<Component>(Entity->GetComponents<BComponent>(), {B}));
	CHECK(CheckRangeEquals<Component>(Entity->GetComponents<CComponent>(), {C}));
	Entity->AddComponent(A2);
	CHECK(CheckRangeEquals<Component>(Entity->GetComponents<AComponent>(), {A, A, A2}));
	CHECK(CheckRangeEquals<Component>(Entity->GetComponents<BComponent>(), {B}));
	CHECK(CheckRangeEquals<Component>(Entity->GetComponents<CComponent>(), {C}));
}

TEST_CASE("IEntity::ExpectSingleComponent")
{
	IEntity<Component> * Entity = new IEntity<Component>();
	AComponent * A = new AComponent(), * ATest = nullptr;
	BComponent * B = new BComponent(), * BTest = nullptr;
	CComponent * C = new CComponent(), * CTest = nullptr;
	AComponent * A2 = new CComponent(), * A2Test = nullptr;

	CHECK(Entity->ExpectSingleComponent(ATest) == 0);
	CHECK(! ATest);
	CHECK(Entity->ExpectSingleComponent(BTest) == 0);
	CHECK(! BTest);
	CHECK(Entity->ExpectSingleComponent(CTest) == 0);
	CHECK(! CTest);

	Entity->AddComponent(A);

	CHECK(Entity->ExpectSingleComponent(ATest) == 1);
	CHECK(ATest == A);
	CHECK(Entity->ExpectSingleComponent(BTest) == 0);
	CHECK(! BTest);
	CHECK(Entity->ExpectSingleComponent(CTest) == 0);
	CHECK(! CTest);

	Entity->AddComponent(A);
	ATest = nullptr;

	CHECK(Entity->ExpectSingleComponent(ATest) == 2);
	CHECK(ATest == A);
	CHECK(Entity->ExpectSingleComponent(BTest) == 0);
	CHECK(! BTest);
	CHECK(Entity->ExpectSingleComponent(CTest) == 0);
	CHECK(! CTest);

	Entity->AddComponent(B);
	Entity->AddComponent(C);
	Entity->AddComponent(A2);
	ATest = nullptr;

	CHECK(Entity->ExpectSingleComponent(ATest) == 3);
	CHECK(ATest == A);
	CHECK(Entity->ExpectSingleComponent(BTest) == 1);
	CHECK(BTest == B);
	CHECK(Entity->ExpectSingleComponent(CTest) == 1);
	CHECK(CTest == C);
}

TEST_CASE("IEntity::CHECKSingleComponent")
{
	IEntity<Component> * Entity = new IEntity<Component>();
	AComponent * ATest = nullptr;
	BComponent * BTest = nullptr;

	CHECK(Entity->GetComponentCount<AComponent>() == 0);
	ATest = Entity->RequireSingleComponent<AComponent>();
	CHECK(ATest);
	CHECK(ATest->foo());
	CHECK(Entity->GetComponentCount<AComponent>() == 1);
	CHECK(CheckRangeEquals<Component>(Entity->GetComponents<AComponent>(), {ATest}));
	CHECK(ATest == Entity->RequireSingleComponent<AComponent>());
	CHECK(Entity->GetComponentCount<AComponent>() == 1);
	CHECK(CheckRangeEquals<Component>(Entity->GetComponents<AComponent>(), {ATest}));

	CHECK(Entity->GetComponentCount<BComponent>() == 0);
	BTest = Entity->RequireSingleComponent<BComponent>();
	CHECK(BTest);
	CHECK(Entity->GetComponentCount<AComponent>() == 1);
	CHECK(Entity->GetComponentCount<BComponent>() == 1);
	CHECK(CheckRangeEquals<Component>(Entity->GetComponents<AComponent>(), {ATest}));
	CHECK(CheckRangeEquals<Component>(Entity->GetComponents<BComponent>(), {BTest}));
	CHECK(BTest == Entity->RequireSingleComponent<BComponent>());
	CHECK(Entity->GetComponentCount<AComponent>() == 1);
	CHECK(Entity->GetComponentCount<BComponent>() == 1);
	CHECK(CheckRangeEquals<Component>(Entity->GetComponents<AComponent>(), {ATest}));
	CHECK(CheckRangeEquals<Component>(Entity->GetComponents<BComponent>(), {BTest}));
}
