
#include "CMeshLibrary.h"


CMesh * CMeshLibrary::Add(string const & Label, CMesh * Mesh)
{
	return Meshes[Label] = Mesh;
}

CMesh * CMeshLibrary::Get(string const & Label)
{
	return ConditionalMapAccess(Meshes, Label);
}

CMesh * CMeshLibrary::Load(string const & File)
{
	CMesh * Mesh = CMesh::Load(File);

	if (Mesh)
		return Meshes[File] = Mesh;

	return 0;
}
