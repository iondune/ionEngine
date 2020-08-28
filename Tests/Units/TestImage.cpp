
#include <ionCore.h>
#include <doctest.h>

using namespace ion;


TEST_CASE("CImage::FlipY")
{
	byte data[] =
	{
		0, 0, 0, 0,
		120, 240, 250, 255,
		40, 50, 60, 90,
		1, 2, 3, 4
	};
	CImage * image = new CImage(data, vec2i(2, 2));

	CHECK(image->GetPixel(0, 0) == color4i(0, 0, 0, 0));
	CHECK(image->GetPixel(1, 0) == color4i(120, 240, 250, 255));
	CHECK(image->GetPixel(0, 1) == color4i(40, 50, 60, 90));
	CHECK(image->GetPixel(1, 1) == color4i(1, 2, 3, 4));

	image->FlipY();

	CHECK(image->GetPixel(0, 1) == color4i(0, 0, 0, 0));
	CHECK(image->GetPixel(1, 1) == color4i(120, 240, 250, 255));
	CHECK(image->GetPixel(0, 0) == color4i(40, 50, 60, 90));
	CHECK(image->GetPixel(1, 0) == color4i(1, 2, 3, 4));
}
