#pragma once

#include "CImage.h"
#include "CTexture.h"

#include <string.h>
#include <string>
#include <map>


class CImageLoader
{

public:
	
	static CImage * LoadImage(std::string const & Name);
	static CTexture * LoadTexture(std::string const & Name, STextureCreationFlags Flags = STextureCreationFlags());
	static CTexture * LoadTexture(CImage * Image, STextureCreationFlags Flags = STextureCreationFlags());
	static void LoadColorTable();

	static std::string ImageDirectory;

private:
	
    static std::map<std::string, CImage *> LoadedImages;
    static std::map<CImage *, CTexture *> LoadedTextures;
	static std::map<std::string, CImage *> ColorTable;

};
