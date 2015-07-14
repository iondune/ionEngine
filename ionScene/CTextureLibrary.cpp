
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

CTexture * CTextureLibrary::Load(string const & File, string const & Label)
{
	string const FileName = MakeFileName(BaseDirectory, File);

	CImage * Image = CImage::Load(FileName);
	CTexture * Texture = nullptr;
	if (Image)
		Texture = Image->MakeTexture();

	return Textures[Label.length() ? Label : File] = Texture;
}

void CTextureLibrary::SetBaseDirectory(string const & BaseDirectory)
{
	this->BaseDirectory = BaseDirectory;
}

string CTextureLibrary::GetBaseDirectory() const
{
	return BaseDirectory;
}
