
#include "CMeshLibrary.h"


CMesh * CMeshLibrary::Add(string const & Label, CMesh * Mesh)
{
	return Meshes[Label] = Mesh;
}

CMesh * CMeshLibrary::Get(string const & Label)
{
	return ConditionalMapAccess(Meshes, Label);
}

static string MakeFileName(string const & BaseDirectory, string const & File)
{
	if (BaseDirectory.length() > 0)
		return BaseDirectory + "/" + File;
	else
		return File;
}

CMesh * CMeshLibrary::Load(string const & File, string const & Label)
{
	CMesh * Mesh = CMesh::Load(MakeFileName(BaseDirectory, File));

	if (Mesh)
		return Meshes[Label.length() ? Label : File] = Mesh;

	return 0;
}

void CMeshLibrary::SetBaseDirectory(string const & BaseDirectory)
{
	this->BaseDirectory = BaseDirectory;
}

string CMeshLibrary::GetBaseDirectory() const
{
	return BaseDirectory;
}
