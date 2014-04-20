
#include "CMesh.h"


void CMesh::SMeshBuffer::UpdateBuffers()
{
	Positions.clear();
	Colors.clear();
	Normals.clear();
	TexCoords.clear();
	Indices.clear();

	for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
		for (uint j = 0; j < 3; ++ j)
			Positions.push_back(it->Position[j]);

	for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
		for (uint j = 0; j < 3; ++ j)
			Colors.push_back(it->Color[j]);

	for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
		for (uint j = 0; j < 3; ++ j)
			Normals.push_back(it->Normal[j]);

	for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
		for (uint j = 0; j < 2; ++ j)
			TexCoords.push_back(it->TextureCoordinates[j]);

	for (std::vector<SMeshTriangle>::iterator it = Triangles.begin(); it != Triangles.end(); ++ it)
		for (uint j = 0; j < 3; ++ j)
			Indices.push_back((* it).Indices[j]);

	Indices.setIsIndexBuffer(true);
}

void CMesh::SMeshBuffer::WriteObjMesh(std::string const & fileName)
{
	std::ofstream File(fileName);

	File << "#vertices" << std::endl;
	for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
		File << "v " << it->Position.X << " " << it->Position.Y << " " << it->Position.Z << std::endl;

	File << "#normals" << std::endl;
	for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
		File << "vn " << it->Normal.X << " " << it->Normal.Y << " " << it->Normal.Z << std::endl;

	File << std::endl << "#faces" << std::endl;
	for (std::vector<SMeshTriangle>::iterator it = Triangles.begin(); it != Triangles.end(); ++ it)
		File << "f " <<
		it->Indices[0] + 1 << "//" << it->Indices[0] + 1 << " " <<
		it->Indices[1] + 1 << "//" << it->Indices[1] + 1 << " " <<
		it->Indices[2] + 1 << "//" << it->Indices[2] + 1 << std::endl;

	File.close();
}
