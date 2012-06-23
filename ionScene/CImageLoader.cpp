#include "CImageLoader.h"

#include <cstdio>
#include <iostream>

struct SBitmapInfo
{
    unsigned int   biSize;           /* Size of info header */
    int            biWidth;          /* Width of image */
    int            biHeight;         /* Height of image */
    unsigned short biPlanes;         /* Number of color planes */
    unsigned short biBitCount;       /* Number of bits per pixel */
    unsigned int   biCompression;    /* Type of compression to use */
    unsigned int   biSizeImage;      /* Size of image data */
    int            biXPelsPerMeter;  /* X pixels per meter */
    int            biYPelsPerMeter;  /* Y pixels per meter */
    unsigned int   biClrUsed;        /* Number of colors used */
    unsigned int   biClrImportant;   /* Number of important colors */
    char *data;
};

#ifdef _WIN32
#pragma warning(disable: 4996)
#endif

std::map<std::string, CImage *> CImageLoader::LoadedImages;
std::map<std::string, CTexture *> CImageLoader::LoadedTextures;

std::string CImageLoader::ImageDirectory = "../Media/Textures/";
std::string & CImageLoader::TextureDirectory = CImageLoader::ImageDirectory;

CTexture * const CImageLoader::loadTexture(std::string const & fileName, bool const useCache)
{
	if (useCache)
	{
		std::map<std::string, CTexture *>::iterator it = LoadedTextures.find(fileName);

		if (it != LoadedTextures.end())
		{
			return it->second;
		}
	}

	CImage * Image = loadImage(fileName, useCache);
	if (! Image)
	{
		std::cerr << "Failed to load image with file name '" << fileName << "', aborting creation of texture." << std::endl;
		return 0;
	}

    CTexture * Texture = new CTexture(Image);

	if (useCache)
		LoadedTextures[fileName] = Texture;

    return Texture;
}

CImage * const CImageLoader::loadImage(std::string const & fileName, bool const useCache)
{
	if (useCache)
	{
		std::map<std::string, CImage *>::iterator it = LoadedImages.find(fileName);

		if (it != LoadedImages.end())
		{
			return it->second;
		}
	}

    FILE * file;
    char temp;
    long i;

    SBitmapInfo infoheader;

    if(fileName.find(".tga") != std::string::npos) {
       return CImageLoader::loadTGAImage(fileName);
    }
    if( (file = fopen((ImageDirectory + fileName).c_str(), "rb"))==NULL)
	{
		std::cerr << "Failed to open bmp image file: '" << (ImageDirectory + fileName) << "'." << std::endl;
        return 0; // Open the file for reading
	}
    fseek(file, 18, SEEK_CUR);  /* start reading width & height */
    fread(&infoheader.biWidth, sizeof(int), 1, file);

    fread(&infoheader.biHeight, sizeof(int), 1, file);

    fread(&infoheader.biPlanes, sizeof(short int), 1, file);
    if (infoheader.biPlanes != 1) {
        printf("Planes from %s is not 1: %u\n", fileName.c_str(), infoheader.biPlanes);
        return 0;
    }

    // read the bpp
    fread(&infoheader.biBitCount, sizeof(unsigned short int), 1, file);
    if (infoheader.biBitCount != 24) {
        printf("Bpp from %s is not 24: %d\n", fileName.c_str(), infoheader.biBitCount);
        return 0;
    }

    fseek(file, 24, SEEK_CUR);

    // read the data.
    infoheader.data = new char[infoheader.biWidth * infoheader.biHeight * 3];
    if (infoheader.data == NULL) {
        printf("Error allocating memory for color-corrected image data\n");
        return 0;
    }

    if ((i = fread(infoheader.data, infoheader.biWidth * infoheader.biHeight * 3, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", fileName.c_str());
        return 0;
    }

    for (i=0; i<(infoheader.biWidth * infoheader.biHeight * 3); i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = infoheader.data[i];
        infoheader.data[i] = infoheader.data[i+2];
        infoheader.data[i+2] = temp;
    }


    fclose(file); // Closes the file stream

    CImage * Image = new CImage((unsigned char *) infoheader.data, infoheader.biWidth, infoheader.biHeight);

	if (useCache)
		LoadedImages[fileName] = Image;

    return Image;
}

#include "ImageLoaders/Texture.h"

CImage * const CImageLoader::loadTGAImage(std::string const & fileName)
{
	Texture tex;
	if (! LoadTGA(& tex, (ImageDirectory + fileName).c_str()))
	{
		std::cerr << "Failed to open tga image file: '" << (ImageDirectory + fileName) << "'." << std::endl;
		return 0;
	}

	CImage * Image = new CImage((unsigned char *)tex.imageData, tex.width, tex.height, tex.bpp == 32);
	char Data[1000];
	memcpy(Data, tex.imageData, 1000);

	return Image;
}
