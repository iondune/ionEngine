#ifndef _CABBAGEGUI_CFONT_H_INCLUDED_
#define _CABBAGEGUI_CFONT_H_INCLUDED_

#include <string>

#include <SColor.h>

#include "CGUIWidget.h"

namespace OGLFT
{
	class Face;
}

class CGUIFontWidget;
class CGUIEngine;
class CApplication;

class CGUIFontWidget : public CGUIWidget
{

	void makeRenderer(std::string const & FileName, float const Size);

	OGLFT::Face * Renderer;
	std::string Text;

	CGUIFontWidget *DropShadow;
	SColorAf const getDropShadowColor();

	std::string FileNameString;
	float FontSize;


public:

	CGUIFontWidget(std::string const & FileName, float const Size);

	void draw();

	void setColor(SColorAf const & Color);
	SColorAf const getColor();

	void setText(std::string const & text);
	std::string const & getText() const;

	void addDropShadow();
	void addDropShadow(SColorAf const & Color);
	void removeDropShadow();
	bool const hasDropShadow();

	void setVisible(bool const visible);

	static std::string FontDirectory;

};

#endif
