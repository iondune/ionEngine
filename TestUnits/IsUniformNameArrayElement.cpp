
#include <ionScene.h>
#include <catch.hpp>


using namespace ion::Scene;

TEST_CASE("IsUniformNameArrayElement")
{
	int Index;
	string LHS;
	string Remaining;

	REQUIRE(IsUniformNameArrayElement("uPointLights[0].Position", Index, LHS, Remaining));
	REQUIRE(Index == 0);
	REQUIRE(LHS == "uPointLights");
	REQUIRE(Remaining == ".Position");

	REQUIRE(! IsUniformNameArrayElement("uPointLights[].Position", Index, LHS, Remaining));
	REQUIRE(! IsUniformNameArrayElement("uPointLights[]", Index, LHS, Remaining));
	REQUIRE(! IsUniformNameArrayElement("uPointLights[", Index, LHS, Remaining));
	REQUIRE(! IsUniformNameArrayElement("uPointLights]0[.Position", Index, LHS, Remaining));

	REQUIRE(IsUniformNameArrayElement("uSphereLights[30].Position", Index, LHS, Remaining));
	REQUIRE(Index == 30);
	REQUIRE(LHS == "uSphereLights");
	REQUIRE(Remaining == ".Position");

	REQUIRE(IsUniformNameArrayElement("uSpotLights[999]", Index, LHS, Remaining));
	REQUIRE(Index == 999);
	REQUIRE(LHS == "uSpotLights");
	REQUIRE(Remaining == "");
}
