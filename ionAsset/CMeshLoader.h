#ifndef _ION_SCENE_CMESHLOADER_H_INCLUDED_
#define _ION_SCENE_CMESHLOADER_H_INCLUDED_

#include "CMesh.h"

#include <string>
#include <map>


class CMeshLoader
{

    static std::map<std::string, CMesh *> LoadedMeshes;

public:

    static CMesh * const loadMesh(std::string const & fileName);

    static CMesh * const createCubeMesh();

    static CMesh * const createPlaneMesh();

    static CMesh * const createDiscMesh(unsigned int const Triangles = 40);
	
    static std::string MeshDirectory;

};

#endif
