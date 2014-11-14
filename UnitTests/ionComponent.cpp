
#include <ionCore.h>
#include <catch.hpp>


class Component
{};

class AComponent : public Component
{};

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
