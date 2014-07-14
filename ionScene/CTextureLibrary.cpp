
#include "CTextureLibrary.h"


CTexture * CTextureLibrary::Get(string const & Label)
{
	return ConditionalMapAccess(Textures, Label);
}

static string MakeFileName(string const & BaseDirectory, string const & File)
{
	if (BaseDirectory.length() > 0)
		return BaseDirectory + "/" + File;
	else
		return File;
}

CTexture * CTextureLibrary::Load(string const & File, STextureParams const & Params)
{
	string const FileName = MakeFileName(BaseDirectory, File);

	CImage * Image = CImage::Load(FileName);
	CTexture * Texture = new CTexture{Image, Params};
	
	return Textures[File] = Texture;
}

void CTextureLibrary::SetBaseDirectory(string const & BaseDirectory)
{
	this->BaseDirectory = BaseDirectory;
}

string CTextureLibrary::GetBaseDirectory() const
{
	return BaseDirectory;
}
