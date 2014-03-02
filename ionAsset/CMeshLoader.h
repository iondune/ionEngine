
#pragma once

#include "CMesh.h"


class CMeshLoader
{

public:

    static CMesh * const LoadMesh(std::string const & fileName);
    static CMesh * const CreateCubeMesh();
    static CMesh * const CreatePlaneMesh();
    static CMesh * const CreateDiscMesh(unsigned int const Triangles = 40);

    static CMesh * const CreateReverseCubeMesh();
	
    static std::string MeshDirectory;

};
