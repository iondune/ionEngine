#ifndef _ION_SCENE_CIMAGELOADER_H_INCLUDED_
#define _ION_SCENE_CIMAGELOADER_H_INCLUDED_

#include "CImage.h"
#include "CTexture.h"

#include <string.h>
#include <string>
#include <map>

class CImageLoader
{

    static std::map<std::string, CImage *> LoadedImages;
    static std::map<std::string, CTexture *> LoadedTextures;

public:

    static CImage * const loadImage(std::string const & fileName, bool const useCache = true);
	static CImage * const loadTGAImage(std::string const & fileName);
    static CTexture * const loadTexture(std::string const & fileName, bool const useCache = true);

	static std::string ImageDirectory;
	static std::string & TextureDirectory;

};

#endif
