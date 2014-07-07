
#pragma once

#include <ionCore.h>
#include <ionGL.h>


class CShaderLibrary
{

public:

	ion::GL::Program * Get(string const & Label);
	ion::GL::Program * Load(string const & File);
	ion::GL::Program * LoadFromSource(string const & Name, string const & VertShaderSource, string const & FragShaderSource);

	void SetBaseDirectory(string const & BaseDirectory);
	string GetBaseDirectory() const;

protected:

	map<string, ion::GL::Program *> Shaders;
	string BaseDirectory;

};
