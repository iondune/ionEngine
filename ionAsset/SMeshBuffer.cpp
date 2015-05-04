
#include "SMeshBuffer.h"


SMeshBuffer::SMeshBuffer()
{}

SMeshBuffer::SMeshBuffer(vector<uint> Indices,
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

		if (i * 2 + 1 < TexCoords.size())
			Vertex.TextureCoordinates = vec2f(TexCoords[i * 2 + 0], TexCoords[i * 2 + 1]);

		Vertices.push_back(Vertex);
	}

	for (uint i = 0; i < Indices.size() / 3; ++ i)
		Triangles.push_back(SMeshTriangle(
		Indices[i * 3 + 0],
		Indices[i * 3 + 1],
		Indices[i * 3 + 2]));
}

void SMeshBuffer::LoadDataIntoBuffers()
{
	if (! VertexBuffers.Positions)
		VertexBuffers.Positions = new ion::GL::VertexBuffer;
	if (! VertexBuffers.Normals)
		VertexBuffers.Normals = new ion::GL::VertexBuffer;
	if (! VertexBuffers.Colors)
		VertexBuffers.Colors = new ion::GL::VertexBuffer;
	if (! VertexBuffers.TexCoords)
		VertexBuffers.TexCoords = new ion::GL::VertexBuffer;
	if (! VertexBuffers.BoneWeights)
		VertexBuffers.BoneWeights = new ion::GL::VertexBuffer;
	if (! VertexBuffers.BoneIndices)
		VertexBuffers.BoneIndices = new ion::GL::VertexBuffer;
	if (! VertexBuffers.Indices)
		VertexBuffers.Indices = new ion::GL::IndexBuffer;

	{
		vector<f32> Data;

		for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
			for (uint j = 0; j < 3; ++ j)
				Data.push_back(it->Position[j]);
		VertexBuffers.Positions->Data(Data, 3);
		Data.clear();

		for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
			for (uint j = 0; j < 3; ++ j)
				Data.push_back(it->Normal[j]);
		VertexBuffers.Normals->Data(Data, 3);
		Data.clear();

		for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
			for (uint j = 0; j < 3; ++ j)
				Data.push_back(it->Color[j]);
		VertexBuffers.Colors->Data(Data, 3);
		Data.clear();

		for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
			for (uint j = 0; j < 2; ++ j)
				Data.push_back(it->TextureCoordinates[j]);
		VertexBuffers.TexCoords->Data(Data, 2);
		Data.clear();

		for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
			for (uint j = 0; j < 2; ++ j)
				Data.push_back(it->BoneWeights[j]);
		VertexBuffers.BoneWeights->Data(Data, 2);
		Data.clear();

		for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
			for (uint j = 0; j < 2; ++ j)
				Data.push_back((float) it->BoneIndices[j]);
		VertexBuffers.BoneIndices->Data(Data, 2);
		Data.clear();
	}

	{
		vector<u32> Data;

		for (std::vector<SMeshTriangle>::iterator it = Triangles.begin(); it != Triangles.end(); ++ it)
			for (uint j = 0; j < 3; ++ j)
				Data.push_back((* it).Indices[j]);
		VertexBuffers.Indices->Data(Data);
		Data.clear();
	}
}

void SMeshBuffer::WriteObjMesh(std::string const & fileName)
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

SMaterial * SMeshBuffer::GetMaterial()
{
	return Material ? Material : (Material = new SMaterial{});
}
