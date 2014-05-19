
#pragma once

#include <ionCore.h>
#include <ionGL.h>


class CShaderLibrary
{

public:

	ion::GL::Program * Get(string const & Label);
	ion::GL::Program * Load(string const & File);

protected:

	map<string, ion::GL::Program *> Shaders;

};
