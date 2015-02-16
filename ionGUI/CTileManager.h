
#pragma once

#include <ionCore.h>
#include <ionGL.h>
#include <ionAsset.h>
#include <ionWindow.h>


class CTile
{

public:

	CTile(ion::GL::Texture * Background, ion::GL::Texture * Hover, ion::GL::Texture * Select, vec2f const & Position, vec2f const & Size);

	vec2f const & GetPosition() const;
	vec2f const & GetSize() const;

	ion::GL::Texture const * GetBackgroundTexture() const;
	ion::GL::Texture const * GetHoverTexture() const;
	ion::GL::Texture const * GetSelectTexture() const;

protected:

	vec2f Position;
	vec2f Size = vec2f(1.f);

	ion::GL::Texture * BackgroundTexture = nullptr;
	ion::GL::Texture * HoverTexture = nullptr;
	ion::GL::Texture * SelectTexture = nullptr;

};

class CMenu
{

public:

	CMenu(ion::GL::Texture * Background);
		
	CTile * AddTile(string const & BackgroundFile, string const & HoverFile, string const & SelectFile, vec2f const & Position, vec2f const & Size = vec2f(1.f));
	ion::GL::Texture const * GetBackgroundTexture() const;

	vector<CTile *> const & GetTiles() const;

protected:

	ion::GL::Texture * BackgroundTexture = nullptr;

	vector<CTile *> Tiles;

};

class CTileManager : public Singleton<CTileManager>
{

public:

	void Init(CWindow * Window);

	CMenu * AddMenu(string const & BackgroundFile);

	void Draw();

protected:

	ion::GL::Program * shader = nullptr;
	ion::GL::DrawConfig * Config = nullptr;

	ion::GL::UniformValue<vec2f> * min = nullptr;
	ion::GL::UniformValue<vec2f> * max = nullptr;
	ion::GL::UniformValue<float> * blend2 = nullptr;
	ion::GL::UniformValue<float> * blend3 = nullptr;

	CWindow * Window = nullptr;

	vector<CMenu *> Menus;

};
