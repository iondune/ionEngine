
#pragma once

#include "CMesh.h"


class CMeshLoader
{

public:

    static CMesh * const LoadMesh(std::string const & fileName);
    static CMesh * const CreateCubeMesh();

    static CMesh * const CreateReverseCubeMesh();

    static std::string MeshDirectory;

};
