#include "CImageLoader.h"

#include <cstdio>
#include <iostream>
#include <stb_image.c>


std::map<std::string, CImage *> CImageLoader::LoadedImages;
std::string CImageLoader::TextureDirectory = "../Media/Textures/";

CTexture * const CImageLoader::LoadTexture(std::string const & fileName, STextureCreationFlags Flags, bool const useCache)
{
	if (useCache)
	{
		std::map<std::string, CImage *>::iterator it = LoadedImages.find(fileName);

		if (it != LoadedImages.end())
		{
			return new CTexture(it->second, Flags);
		}
	}

	int x, y, n;
	u8 * data = stbi_load((TextureDirectory + fileName).c_str(), &x, &y, &n, 0);

	if (! data)
	{
		std::cerr << "Failed to load image with file name '" << fileName << "', aborting creation of texture." << std::endl;
		return 0;
	}

    CImage * Image = new CImage(data, x, y);

	if (useCache)
		LoadedImages[fileName] = Image;

    return new CTexture(Image, Flags);
}
