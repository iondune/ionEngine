#pragma once

#include "CImage.h"
#include "CTexture.h"

#include <string.h>
#include <string>
#include <map>


class CImageLoader
{

    static std::map<std::string, CImage *> LoadedImages;

public:

	static CTexture * const LoadTexture(std::string const & FileName, STextureCreationFlags Flags = STextureCreationFlags(), bool const useCache = true);

	static std::string TextureDirectory;

};
