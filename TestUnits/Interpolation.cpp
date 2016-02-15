
#include <ionScience.h>
#include <catch.hpp>


TEST_CASE("Linear interpolation (3) works", "[LinearInterpolation]") {
	REQUIRE(LinearInterpolate(0.0, 1.0, 0.5) == 0.5);
	REQUIRE(LinearInterpolate(-1.0, 1.0, 0.5) == 0.0);
	REQUIRE(LinearInterpolate(-1.0, 1.0, 0.25) == -0.5);
	REQUIRE(LinearInterpolate(-1.0, 1.0, 0.75) == 0.5);
}

TEST_CASE("Linear interpolation (2) works", "[LinearInterpolation]") {
	std::array<double, 2> p;

	p = {{0, 1}};
	REQUIRE(LinearInterpolate(p.data(), 0.5) == 0.5);
	p = {{-1, 1}};
	REQUIRE(LinearInterpolate(p.data(), 0.5) == 0.0);
	REQUIRE(LinearInterpolate(p.data(), 0.25) == -0.5);
	REQUIRE(LinearInterpolate(p.data(), 0.75) == 0.5);
}

TEST_CASE("Bilinear interpolation works", "[BilinearInterpolate]") {
	double p[2][2];

	p[0][0] = 1;
	p[0][1] = 2;
	p[1][0] = 3;
	p[1][1] = 4;
	REQUIRE(BilinearInterpolate(p, 0.0, 0.0) == 1.0);
	REQUIRE(BilinearInterpolate(p, 0.0, 1.0) == 2.0);
	REQUIRE(BilinearInterpolate(p, 1.0, 0.0) == 3.0);
	REQUIRE(BilinearInterpolate(p, 1.0, 1.0) == 4.0);

	REQUIRE(BilinearInterpolate(p, 0.0, 0.5) == 1.5);
	REQUIRE(BilinearInterpolate(p, 0.5, 0.0) == 2.0);
	REQUIRE(BilinearInterpolate(p, 1.0, 0.5) == 3.5);
	REQUIRE(BilinearInterpolate(p, 0.5, 1.0) == 3.0);

	REQUIRE(BilinearInterpolate(p, 0.5, 0.5) == 2.5);
}

TEST_CASE("Trilinear interpolation works", "[TrilinearInterpolate]") {
	double p[2][2][2];

	p[0][0][0] = 1;
	p[0][0][1] = 2;
	p[0][1][0] = 3;
	p[0][1][1] = 4;
	p[1][0][0] = 5;
	p[1][0][1] = 6;
	p[1][1][0] = 7;
	p[1][1][1] = 8;

	REQUIRE(TrilinearInterpolate(p, 0.0, 0.0, 0.0) == 1.0);
	REQUIRE(TrilinearInterpolate(p, 0.0, 0.0, 1.0) == 2.0);
	REQUIRE(TrilinearInterpolate(p, 0.0, 1.0, 0.0) == 3.0);
	REQUIRE(TrilinearInterpolate(p, 0.0, 1.0, 1.0) == 4.0);
	REQUIRE(TrilinearInterpolate(p, 1.0, 0.0, 0.0) == 5.0);
	REQUIRE(TrilinearInterpolate(p, 1.0, 0.0, 1.0) == 6.0);
	REQUIRE(TrilinearInterpolate(p, 1.0, 1.0, 0.0) == 7.0);
	REQUIRE(TrilinearInterpolate(p, 1.0, 1.0, 1.0) == 8.0);

	REQUIRE(TrilinearInterpolate(p, 0.0, 0.0, 0.5) == 1.5);
	REQUIRE(TrilinearInterpolate(p, 0.0, 0.5, 0.0) == 2.0);
	REQUIRE(TrilinearInterpolate(p, 0.0, 1.0, 0.5) == 3.5);
	REQUIRE(TrilinearInterpolate(p, 0.0, 0.5, 1.0) == 3.0);
	REQUIRE(TrilinearInterpolate(p, 0.5, 0.0, 0.0) == 3.0);
	REQUIRE(TrilinearInterpolate(p, 0.5, 0.0, 1.0) == 4.0);
	REQUIRE(TrilinearInterpolate(p, 0.5, 1.0, 0.0) == 5.0);
	REQUIRE(TrilinearInterpolate(p, 0.5, 1.0, 1.0) == 6.0);
	REQUIRE(TrilinearInterpolate(p, 1.0, 0.0, 0.5) == 5.5);
	REQUIRE(TrilinearInterpolate(p, 1.0, 0.5, 0.0) == 6.0);
	REQUIRE(TrilinearInterpolate(p, 1.0, 1.0, 0.5) == 7.5);
	REQUIRE(TrilinearInterpolate(p, 1.0, 0.5, 1.0) == 7.0);

	REQUIRE(TrilinearInterpolate(p, 0.0, 0.5, 0.5) == 2.5);
	REQUIRE(TrilinearInterpolate(p, 0.5, 0.0, 0.5) == 3.5);
	REQUIRE(TrilinearInterpolate(p, 0.5, 0.5, 0.0) == 4.0);

	REQUIRE(TrilinearInterpolate(p, 0.5, 0.5, 0.5) == 4.5);
}

TEST_CASE("Cubic interpolation works", "[CubicInterpolate]") {
	std::array<double, 4> p;

	p = {{0, 1, 2, 3}};
	REQUIRE(CubicInterpolate(p.data(), 0.0) == 1.0);
	REQUIRE(CubicInterpolate(p.data(), 0.5) == 1.5);
	REQUIRE(CubicInterpolate(p.data(), 1.0) == 2.0);
	REQUIRE(CubicInterpolate(p.data(), 0.25) == 1.25);
	REQUIRE(CubicInterpolate(p.data(), 0.75) == 1.75);

	p = {{0, 1, 3, 4}};
	REQUIRE(CubicInterpolate(p.data(), 0.0) == 1.0);
	REQUIRE(CubicInterpolate(p.data(), 0.5) == 2.0);
	REQUIRE(CubicInterpolate(p.data(), 1.0) == 3.0);
}
