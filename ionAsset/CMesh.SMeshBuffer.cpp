
#include "CMesh.h"


CMesh::SMeshBuffer::SMeshBuffer()
{
	Positions = 0;
	Colors = 0;
	Normals = 0;
	TexCoords = 0;
	Indices = 0;
	ArrayObject = 0;
}

CMesh::SMeshBuffer::SMeshBuffer(vector<uint> Indices,
	vector<f32> const & Positions,
	vector<f32> const & Normals,
	vector<f32> const & Colors,
	vector<f32> const & TexCoords)
	: SMeshBuffer()
{
	for (uint i = 0; i < Positions.size() / 3; ++ i)
	{
		SVertex Vertex;

		Vertex.Position = vec3f(Positions[i * 3 + 0], Positions[i * 3 + 1], Positions[i * 3 + 2]);

		if (i * 3 + 2 < Normals.size())
			Vertex.Normal = vec3f(Normals[i * 3 + 0], Normals[i * 3 + 1], Normals[i * 3 + 2]);

		if (i * 4 + 3 < Colors.size())
			Vertex.Color = color4f(Colors[i * 4 + 0], Colors[i * 4 + 1], Colors[i * 4 + 2], Colors[i * 4 + 3]);

		if (i * 3 + 2 < TexCoords.size())
			Vertex.TextureCoordinates = vec2f(TexCoords[i * 3 + 0], TexCoords[i * 3 + 1]);

		Vertices.push_back(Vertex);
	}

	for (uint i = 0; i < Indices.size() / 3; ++ i)
		Triangles.push_back(SMeshTriangle(
		Indices[i * 3 + 0],
		Indices[i * 3 + 1],
		Indices[i * 3 + 2]));
}

void CMesh::SMeshBuffer::UpdateBuffers()
{
	if (! Positions)
		Positions = new ion::GL::VertexBuffer;
	if (! Normals)
		Normals = new ion::GL::VertexBuffer;
	if (! Colors)
		Colors = new ion::GL::VertexBuffer;
	if (! TexCoords)
		TexCoords = new ion::GL::VertexBuffer;
	if (! Indices)
		Indices = new ion::GL::IndexBuffer;
	if (! ArrayObject)
		ArrayObject = new ion::GL::VertexArray;

	{
		vector<f32> Data;

		for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
			for (uint j = 0; j < 3; ++ j)
				Data.push_back(it->Position[j]);
		Positions->Data(Data, 3);
		Data.clear();

		for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
			for (uint j = 0; j < 3; ++ j)
				Data.push_back(it->Normal[j]);
		Normals->Data(Data, 3);
		Data.clear();

		for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
			for (uint j = 0; j < 3; ++ j)
				Data.push_back(it->Color[j]);
		Colors->Data(Data, 3);
		Data.clear();

		for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
			for (uint j = 0; j < 2; ++ j)
				Data.push_back(it->TextureCoordinates[j]);
		TexCoords->Data(Data, 2);
		Data.clear();
	}

	{
		vector<u32> Data;

		for (std::vector<SMeshTriangle>::iterator it = Triangles.begin(); it != Triangles.end(); ++ it)
			for (uint j = 0; j < 3; ++ j)
				Data.push_back((* it).Indices[j]);
		Indices->Data(Data);
		Data.clear();
	}

	ArrayObject->SetIndexBuffer(Indices);
	ArrayObject->BindAttribute(0, Positions);
	ArrayObject->BindAttribute(1, Normals);
	ArrayObject->BindAttribute(2, Colors);
	ArrayObject->BindAttribute(3, TexCoords);
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
