
#include <ionScene.h>
#include <catch.hpp>


using namespace ion::Scene;

TEST_CASE("IsUniformNameArrayElement")
{
	int Index;
	string LHS;
	string Remaining;

	CHECK(IsUniformNameArrayElement("uPointLights[0].Position", Index, LHS, Remaining));
	CHECK(Index == 0);
	CHECK(LHS == "uPointLights");
	CHECK(Remaining == ".Position");

	CHECK(! IsUniformNameArrayElement("uPointLights[].Position", Index, LHS, Remaining));
	CHECK(! IsUniformNameArrayElement("uPointLights[]", Index, LHS, Remaining));
	CHECK(! IsUniformNameArrayElement("uPointLights[", Index, LHS, Remaining));
	CHECK(! IsUniformNameArrayElement("uPointLights]0[.Position", Index, LHS, Remaining));

	CHECK(IsUniformNameArrayElement("uSphereLights[30].Position", Index, LHS, Remaining));
	CHECK(Index == 30);
	CHECK(LHS == "uSphereLights");
	CHECK(Remaining == ".Position");

	CHECK(IsUniformNameArrayElement("uSpotLights[999]", Index, LHS, Remaining));
	CHECK(Index == 999);
	CHECK(LHS == "uSpotLights");
	CHECK(Remaining == "");
}
