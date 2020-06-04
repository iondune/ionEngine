
#include <ionCore.h>
#include <doctest.h>

using namespace ion;


TEST_CASE("File::StripExtension")
{
	CHECK(File::StripExtension("") == "");
	CHECK(File::StripExtension("a") == "a");
	CHECK(File::StripExtension(".") == "");
	CHECK(File::StripExtension("File.ext") == "File");
	CHECK(File::StripExtension("File.extension") == "File");
	CHECK(File::StripExtension("File.with.extension") == "File.with");
}

TEST_CASE("File::GetExtension")
{
	CHECK(File::GetExtension("") == "");
	CHECK(File::GetExtension("a") == "");
	CHECK(File::GetExtension(".") == "");
	CHECK(File::GetExtension("File.ext") == "ext");
	CHECK(File::GetExtension("File.extension") == "extension");
	CHECK(File::GetExtension("File.with.extension") == "extension");
}
