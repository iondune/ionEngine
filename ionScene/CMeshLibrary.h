
#pragma once

#include <ionCore.h>
#include <ionGL.h>
#include <ionAsset.h>


class CMeshLibrary
{

public:

	CMesh * Get(string const & Label);
	CMesh * Load(string const & File, string const & Label = "");
	CMesh * Add(string const & Label, CMesh * Mesh);
	
	void SetBaseDirectory(string const & BaseDirectory);
	string GetBaseDirectory() const;

protected:

	map<string, CMesh *> Meshes;
	string BaseDirectory;

};
