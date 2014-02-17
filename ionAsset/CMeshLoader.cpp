
#include "CMeshLoader.h"


std::string CMeshLoader::MeshDirectory = "../Media/Models/";


CMesh * const CMeshLoader::LoadMesh(std::string const & FileName)
{
	return CMesh::Load(MeshDirectory + FileName);
}

CMesh * const CMeshLoader::CreateCubeMesh()
{
    CMesh * MeshWrapper = new CMesh();
    CMesh::SMeshBuffer * Mesh = new CMesh::SMeshBuffer();

    Mesh->Vertices.resize(24);
    Mesh->Vertices[0].Position = SVector3f(-0.5, -0.5, -0.5);
    Mesh->Vertices[1].Position = SVector3f(-0.5,  0.5, -0.5);
    Mesh->Vertices[2].Position = SVector3f( 0.5,  0.5, -0.5);
    Mesh->Vertices[3].Position = SVector3f( 0.5, -0.5, -0.5);

    Mesh->Vertices[4].Position = SVector3f( 0.5, -0.5, -0.5);
    Mesh->Vertices[5].Position = SVector3f( 0.5, 0.5, -0.5);
    Mesh->Vertices[6].Position = SVector3f( 0.5, 0.5,  0.5);
    Mesh->Vertices[7].Position = SVector3f( 0.5, -0.5,  0.5);

    Mesh->Vertices[8].Position = SVector3f( 0.5, -0.5,  0.5);
    Mesh->Vertices[9].Position = SVector3f( 0.5,  0.5,  0.5);
    Mesh->Vertices[10].Position = SVector3f(-0.5,  0.5,  0.5);
    Mesh->Vertices[11].Position = SVector3f(-0.5, -0.5,  0.5);

    Mesh->Vertices[12].Position = SVector3f(-0.5, -0.5,  0.5);
    Mesh->Vertices[13].Position = SVector3f(-0.5,  0.5,  0.5);
    Mesh->Vertices[14].Position = SVector3f(-0.5,  0.5, -0.5);
    Mesh->Vertices[15].Position = SVector3f(-0.5, -0.5, -0.5);

    Mesh->Vertices[16].Position = SVector3f(-0.5,  0.5, -0.5);
    Mesh->Vertices[17].Position = SVector3f(-0.5,  0.5,  0.5);
    Mesh->Vertices[18].Position = SVector3f( 0.5,  0.5,  0.5);
    Mesh->Vertices[19].Position = SVector3f( 0.5,  0.5, -0.5);

    Mesh->Vertices[20].Position = SVector3f( 0.5, -0.5, -0.5);
    Mesh->Vertices[21].Position = SVector3f( 0.5, -0.5,  0.5);
    Mesh->Vertices[22].Position = SVector3f(-0.5, -0.5,  0.5);
    Mesh->Vertices[23].Position = SVector3f(-0.5, -0.5, -0.5);

    Mesh->Triangles.resize(12);
    for (int i = 0; i < 6; ++ i)
    {
        Mesh->Vertices[4*i + 0].TextureCoordinates = SVector2f(0, 1);
        Mesh->Vertices[4*i + 1].TextureCoordinates = SVector2f(0, 0);
        Mesh->Vertices[4*i + 2].TextureCoordinates = SVector2f(1, 0);
        Mesh->Vertices[4*i + 3].TextureCoordinates = SVector2f(1, 1);

        Mesh->Triangles[2*i].Indices[0] = 4*i + 0;
        Mesh->Triangles[2*i].Indices[1] = 4*i + 1;
        Mesh->Triangles[2*i].Indices[2] = 4*i + 2;

        Mesh->Triangles[2*i+1].Indices[0] = 4*i + 0;
        Mesh->Triangles[2*i+1].Indices[1] = 4*i + 2;
        Mesh->Triangles[2*i+1].Indices[2] = 4*i + 3;
    }

    MeshWrapper->MeshBuffers.push_back(Mesh);

    MeshWrapper->calculateNormalsPerFace();
    return MeshWrapper;
}

CMesh * const CMeshLoader::CreatePlaneMesh()
{
    CMesh * MeshWrapper = new CMesh();
    CMesh::SMeshBuffer * Mesh = new CMesh::SMeshBuffer();

    Mesh->Vertices.resize(4);
    Mesh->Vertices[0].Position = SVector3f(-0.5, 0, -0.5);
    Mesh->Vertices[1].Position = SVector3f(-0.5, 0,  0.5);
    Mesh->Vertices[2].Position = SVector3f( 0.5, 0,  0.5);
    Mesh->Vertices[3].Position = SVector3f( 0.5, 0, -0.5);

    Mesh->Vertices[0].TextureCoordinates = SVector2f(0, 1);
    Mesh->Vertices[1].TextureCoordinates = SVector2f(0, 0);
    Mesh->Vertices[2].TextureCoordinates = SVector2f(1, 0);
    Mesh->Vertices[3].TextureCoordinates = SVector2f(1, 1);
	
    Mesh->Triangles.resize(2);
    Mesh->Triangles[0].Indices[0] = 0;
    Mesh->Triangles[0].Indices[1] = 1;
    Mesh->Triangles[0].Indices[2] = 2;

    Mesh->Triangles[1].Indices[0] = 0;
    Mesh->Triangles[1].Indices[1] = 2;
    Mesh->Triangles[1].Indices[2] = 3;

    MeshWrapper->MeshBuffers.push_back(Mesh);
    MeshWrapper->calculateNormalsPerFace();
    return MeshWrapper;
}

CMesh * const CMeshLoader::CreateDiscMesh(unsigned int const Triangles)
{
    CMesh * MeshWrapper = new CMesh();
    CMesh::SMeshBuffer * Mesh = new CMesh::SMeshBuffer();

    Mesh->Vertices.resize(Triangles * 3);
    Mesh->Triangles.resize(Triangles);

    for (unsigned int i = 0; i < Triangles; ++ i)
    {
        Mesh->Vertices[i*3 + 0].Position.X = 0;
        Mesh->Vertices[i*3 + 0].Position.Y = 0;
        Mesh->Vertices[i*3 + 0].Position.Z = 0;

        Mesh->Vertices[i*3 + 1].Position.X = 0.5f * sin(float(i) / float(Triangles) * 2.f * 3.14159f);
        Mesh->Vertices[i*3 + 1].Position.Y = 0;
        Mesh->Vertices[i*3 + 1].Position.Z = 0.5f * cos(float(i) / float(Triangles) * 2.f * 3.14159f);

        Mesh->Vertices[i*3 + 2].Position.X = 0.5f * sin(float(i+1) / float(Triangles) * 2.f * 3.14159f);
        Mesh->Vertices[i*3 + 2].Position.Y = 0;
        Mesh->Vertices[i*3 + 2].Position.Z = 0.5f * cos(float(i+1) / float(Triangles) * 2.f * 3.14159f);

		Mesh->Vertices[i*3 + 0].Normal = SVector3f(0, 0, 1);
		Mesh->Vertices[i*3 + 1].Normal = SVector3f(0, 0, 1);
		Mesh->Vertices[i*3 + 2].Normal = SVector3f(0, 0, 1);

        Mesh->Triangles[i].Indices[0] = i*3 + 0;
        Mesh->Triangles[i].Indices[1] = i*3 + 1;
        Mesh->Triangles[i].Indices[2] = i*3 + 2;
    }

    for (unsigned int i = 0; i < Mesh->Vertices.size(); ++ i)
    {
        Mesh->Vertices[i].TextureCoordinates = SVector2f(Mesh->Vertices[i].Position.X, Mesh->Vertices[i].Position.Y) + SVector2f(0.5f);
    }

    MeshWrapper->MeshBuffers.push_back(Mesh);

    MeshWrapper->calculateNormalsPerFace();
    return MeshWrapper;
}
