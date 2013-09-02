#include "CImageLoader.h"

#include <cstdio>
#include <iostream>


std::map<std::string, CImage *> CImageLoader::LoadedImages;
std::string CImageLoader::TextureDirectory = "../Media/Textures/";

CTexture * const CImageLoader::LoadTexture(std::string const & FileName, STextureCreationFlags Flags, bool const useCache)
{
	if (useCache)
	{
		std::map<std::string, CImage *>::iterator it = LoadedImages.find(FileName);

		if (it != LoadedImages.end())
		{
			return new CTexture(it->second, Flags);
		}
	}

	CImage * Image = CImage::Load(TextureDirectory + FileName);

	if (! Image)
	{
		std::cerr << "Failed to load image with file name '" << FileName << "', aborting creation of texture." << std::endl;
		return 0;
	}

	if (useCache)
		LoadedImages[FileName] = Image;

	return new CTexture(Image, Flags);
}
