
#include <ionCore.h>
#include <catch.hpp>


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

	REQUIRE(A == Entity->AddComponent(A));
	REQUIRE(A == Entity->AddComponent(A));
	REQUIRE(B == Entity->AddComponent(B));
	REQUIRE(C == Entity->AddComponent(C));
	REQUIRE(A2 == Entity->AddComponent(A2));
}

TEST_CASE("IEntity::GetComponentCount")
{
	IEntity<Component> * Entity = new IEntity<Component>();
	AComponent * A = new AComponent();
	BComponent * B = new BComponent();
	CComponent * C = new CComponent();
	AComponent * A2 = new CComponent();

	REQUIRE(Entity->GetComponentCount<AComponent>() == 0);
	REQUIRE(Entity->GetComponentCount<BComponent>() == 0);
	REQUIRE(Entity->GetComponentCount<CComponent>() == 0);
	Entity->AddComponent(A);
	REQUIRE(Entity->GetComponentCount<AComponent>() == 1);
	REQUIRE(Entity->GetComponentCount<BComponent>() == 0);
	REQUIRE(Entity->GetComponentCount<CComponent>() == 0);
	Entity->AddComponent(A);
	REQUIRE(Entity->GetComponentCount<AComponent>() == 2);
	REQUIRE(Entity->GetComponentCount<BComponent>() == 0);
	REQUIRE(Entity->GetComponentCount<CComponent>() == 0);
	Entity->AddComponent(B);
	REQUIRE(Entity->GetComponentCount<AComponent>() == 2);
	REQUIRE(Entity->GetComponentCount<BComponent>() == 1);
	REQUIRE(Entity->GetComponentCount<CComponent>() == 0);
	Entity->AddComponent(C);
	REQUIRE(Entity->GetComponentCount<AComponent>() == 2);
	REQUIRE(Entity->GetComponentCount<BComponent>() == 1);
	REQUIRE(Entity->GetComponentCount<CComponent>() == 1);
	Entity->AddComponent(A2);
	REQUIRE(Entity->GetComponentCount<AComponent>() == 3);
	REQUIRE(Entity->GetComponentCount<BComponent>() == 1);
	REQUIRE(Entity->GetComponentCount<CComponent>() == 1);
}

template <typename TComponent>
bool CheckRangeEquals(pair<typename multimap<Type, TComponent *>::iterator, typename multimap<Type, TComponent *>::iterator> const Iterators, std::initializer_list<TComponent *> const & List)
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

	REQUIRE(CheckRangeEquals<Component>(Entity->GetComponents<AComponent>(), {}));
	REQUIRE(CheckRangeEquals<Component>(Entity->GetComponents<BComponent>(), {}));
	REQUIRE(CheckRangeEquals<Component>(Entity->GetComponents<CComponent>(), {}));
	Entity->AddComponent(A);
	REQUIRE(CheckRangeEquals<Component>(Entity->GetComponents<AComponent>(), {A}));
	REQUIRE(CheckRangeEquals<Component>(Entity->GetComponents<BComponent>(), {}));
	REQUIRE(CheckRangeEquals<Component>(Entity->GetComponents<CComponent>(), {}));
	Entity->AddComponent(A);
	REQUIRE(CheckRangeEquals<Component>(Entity->GetComponents<AComponent>(), {A, A}));
	REQUIRE(CheckRangeEquals<Component>(Entity->GetComponents<BComponent>(), {}));
	REQUIRE(CheckRangeEquals<Component>(Entity->GetComponents<CComponent>(), {}));
	Entity->AddComponent(B);
	REQUIRE(CheckRangeEquals<Component>(Entity->GetComponents<AComponent>(), {A, A}));
	REQUIRE(CheckRangeEquals<Component>(Entity->GetComponents<BComponent>(), {B}));
	REQUIRE(CheckRangeEquals<Component>(Entity->GetComponents<CComponent>(), {}));
	Entity->AddComponent(C);
	REQUIRE(CheckRangeEquals<Component>(Entity->GetComponents<AComponent>(), {A, A}));
	REQUIRE(CheckRangeEquals<Component>(Entity->GetComponents<BComponent>(), {B}));
	REQUIRE(CheckRangeEquals<Component>(Entity->GetComponents<CComponent>(), {C}));
	Entity->AddComponent(A2);
	REQUIRE(CheckRangeEquals<Component>(Entity->GetComponents<AComponent>(), {A, A, A2}));
	REQUIRE(CheckRangeEquals<Component>(Entity->GetComponents<BComponent>(), {B}));
	REQUIRE(CheckRangeEquals<Component>(Entity->GetComponents<CComponent>(), {C}));
}

TEST_CASE("IEntity::ExpectSingleComponent")
{
	IEntity<Component> * Entity = new IEntity<Component>();
	AComponent * A = new AComponent(), * ATest = nullptr;
	BComponent * B = new BComponent(), * BTest = nullptr;
	CComponent * C = new CComponent(), * CTest = nullptr;
	AComponent * A2 = new CComponent(), * A2Test = nullptr;

	REQUIRE(Entity->ExpectSingleComponent(ATest) == 0);
	REQUIRE(! ATest);
	REQUIRE(Entity->ExpectSingleComponent(BTest) == 0);
	REQUIRE(! BTest);
	REQUIRE(Entity->ExpectSingleComponent(CTest) == 0);
	REQUIRE(! CTest);

	Entity->AddComponent(A);

	REQUIRE(Entity->ExpectSingleComponent(ATest) == 1);
	REQUIRE(ATest == A);
	REQUIRE(Entity->ExpectSingleComponent(BTest) == 0);
	REQUIRE(! BTest);
	REQUIRE(Entity->ExpectSingleComponent(CTest) == 0);
	REQUIRE(! CTest);

	Entity->AddComponent(A);
	ATest = nullptr;

	REQUIRE(Entity->ExpectSingleComponent(ATest) == 2);
	REQUIRE(ATest == A);
	REQUIRE(Entity->ExpectSingleComponent(BTest) == 0);
	REQUIRE(! BTest);
	REQUIRE(Entity->ExpectSingleComponent(CTest) == 0);
	REQUIRE(! CTest);

	Entity->AddComponent(B);
	Entity->AddComponent(C);
	Entity->AddComponent(A2);
	ATest = nullptr;

	REQUIRE(Entity->ExpectSingleComponent(ATest) == 3);
	REQUIRE(ATest == A);
	REQUIRE(Entity->ExpectSingleComponent(BTest) == 1);
	REQUIRE(BTest == B);
	REQUIRE(Entity->ExpectSingleComponent(CTest) == 1);
	REQUIRE(CTest == C);
}

TEST_CASE("IEntity::RequireSingleComponent")
{
	IEntity<Component> * Entity = new IEntity<Component>();
	AComponent * ATest = nullptr;
	BComponent * BTest = nullptr;

	REQUIRE(Entity->GetComponentCount<AComponent>() == 0);
	ATest = Entity->RequireSingleComponent<AComponent>();
	REQUIRE(ATest);
	REQUIRE(ATest->foo());
	REQUIRE(Entity->GetComponentCount<AComponent>() == 1);
	REQUIRE(CheckRangeEquals<Component>(Entity->GetComponents<AComponent>(), {ATest}));
	REQUIRE(ATest == Entity->RequireSingleComponent<AComponent>());
	REQUIRE(Entity->GetComponentCount<AComponent>() == 1);
	REQUIRE(CheckRangeEquals<Component>(Entity->GetComponents<AComponent>(), {ATest}));

	REQUIRE(Entity->GetComponentCount<BComponent>() == 0);
	BTest = Entity->RequireSingleComponent<BComponent>();
	REQUIRE(BTest);
	REQUIRE(Entity->GetComponentCount<AComponent>() == 1);
	REQUIRE(Entity->GetComponentCount<BComponent>() == 1);
	REQUIRE(CheckRangeEquals<Component>(Entity->GetComponents<AComponent>(), {ATest}));
	REQUIRE(CheckRangeEquals<Component>(Entity->GetComponents<BComponent>(), {BTest}));
	REQUIRE(BTest == Entity->RequireSingleComponent<BComponent>());
	REQUIRE(Entity->GetComponentCount<AComponent>() == 1);
	REQUIRE(Entity->GetComponentCount<BComponent>() == 1);
	REQUIRE(CheckRangeEquals<Component>(Entity->GetComponents<AComponent>(), {ATest}));
	REQUIRE(CheckRangeEquals<Component>(Entity->GetComponents<BComponent>(), {BTest}));
}
