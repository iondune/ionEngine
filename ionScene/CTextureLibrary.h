
#pragma once

#include <ionCore.h>
#include <ionAsset.h>


class CTextureLibrary
{

public:

	CTexture * Get(string const & Label);
	CTexture * Load(string const & File, STextureParams const & Params = STextureParams{});

	void SetBaseDirectory(string const & BaseDirectory);
	string GetBaseDirectory() const;

protected:

	map<string, CTexture *> Textures;
	string BaseDirectory;

};
