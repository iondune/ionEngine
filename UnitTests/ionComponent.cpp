
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
	REQUIRE(B == Entity->AddComponent(B));
	REQUIRE(C == Entity->AddComponent(C));
	REQUIRE(A2 == Entity->AddComponent(A2));
}
