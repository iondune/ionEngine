#include "CImageLoader.h"

#include <cstdio>
#include <iostream>


std::map<std::string, CImage *> CImageLoader::LoadedImages;
std::map<CImage *, CTexture *> CImageLoader::LoadedTextures;
std::map<std::string, CImage *> CImageLoader::ColorTable;
std::string CImageLoader::ImageDirectory = "../Media/Textures/";

CImage * CImageLoader::LoadImage(std::string const & Name)
{
	if (ColorTable.empty())
		LoadColorTable();
	
	auto it = ColorTable.find(Name);
	if (it != ColorTable.end())
		return it->second;

	it = LoadedImages.find(Name);
	if (it != LoadedImages.end())
		return it->second;

	CImage * Image = CImage::Load(ImageDirectory + Name);
	if (! Image)
	{
		std::cerr << "Failed to load image with name '" << Name << "'" << std::endl;
		return 0;
	}

	LoadedImages[Name] = Image;
	return Image;
}

CTexture * CImageLoader::LoadTexture(std::string const & Name, STextureCreationFlags Flags)
{
	return LoadTexture(LoadImage(Name));
}

CTexture * CImageLoader::LoadTexture(CImage * Image, STextureCreationFlags Flags)
{
	if (! Image)
	{
		std::cerr << "Aborting creation of texture." << std::endl;
		return 0;
	}

	auto it = LoadedTextures.find(Image);
	if (it != LoadedTextures.end())
		return it->second;

	CTexture * Texture = new CTexture(Image, Flags);
	LoadedTextures[Image] = Texture;
	return Texture;
}

void CImageLoader::LoadColorTable()
{
	ColorTable.clear();
	
	ColorTable["Black"] = new CImage(Colors::Black);
	ColorTable["Red"] = new CImage(Colors::Red);
	ColorTable["Green"] = new CImage(Colors::Green);
	ColorTable["Blue"] = new CImage(Colors::Blue);
	ColorTable["Yellow"] = new CImage(Colors::Yellow);
	ColorTable["Orange"] = new CImage(Colors::Orange);
	ColorTable["Magenta"] = new CImage(Colors::Magenta);
	ColorTable["Cyan"] = new CImage(Colors::Cyan);
	ColorTable["White"] = new CImage(Colors::White);

	ColorTable["Grey1"] = new CImage(color3f(0.1f));
	ColorTable["Grey2"] = new CImage(color3f(0.2f));
	ColorTable["Grey3"] = new CImage(color3f(0.3f));
	ColorTable["Grey4"] = new CImage(color3f(0.4f));
	ColorTable["Grey5"] = new CImage(color3f(0.5f));
	ColorTable["Grey6"] = new CImage(color3f(0.6f));
	ColorTable["Grey7"] = new CImage(color3f(0.7f));
	ColorTable["Grey8"] = new CImage(color3f(0.8f));
	ColorTable["Grey9"] = new CImage(color3f(0.9f));
}
