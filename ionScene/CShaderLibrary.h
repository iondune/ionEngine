
#pragma once

#include <ionCore.h>
#include <ionAsset.h>


class CShaderLibrary
{

public:

	CShader * Get(string const & Label);
	CShader * Load(string const & File);
	CShader * Load(string const & Name, string const & VertexFile, string const & FragFile);
	CShader * Load(string const & Name, string const & VertexFile, string const & GeomFile, string const & FragFile);
	CShader * LoadFromSource(string const & Name, string const & VertShaderSource, string const & GeomShaderSource, string const & FragShaderSource);

	void SetBaseDirectory(string const & BaseDirectory);
	string GetBaseDirectory() const;

protected:

	map<string, CShader *> Shaders;
	string BaseDirectory;

};
