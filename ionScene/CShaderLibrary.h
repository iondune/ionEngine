
#pragma once

#include <ionCore.h>
#include <ionAsset.h>


class CShaderLibrary
{

public:

	CShader * Get(string const & Label);
	CShader * Load(string const & File);
	CShader * LoadFromSource(string const & Name, string const & VertShaderSource, string const & FragShaderSource);

	void SetBaseDirectory(string const & BaseDirectory);
	string GetBaseDirectory() const;

protected:

	map<string, CShader *> Shaders;
	string BaseDirectory;

};
