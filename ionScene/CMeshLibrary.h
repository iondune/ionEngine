
#pragma once

#include <ionCore.h>
#include <ionGL.h>
#include <ionAsset.h>


class CMeshLibrary
{

public:

	CMesh * Get(string const & Label);
	CMesh * Load(string const & File);
	CMesh * Add(string const & Label, CMesh * Mesh);

protected:

	map<string, CMesh *> Meshes;

};
