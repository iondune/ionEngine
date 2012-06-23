#ifndef _CABBAGEGUI_CDIALOG_H_INCLUDED_
#define _CABBAGEGUI_CDIALOG_H_INCLUDED_

#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#include "CGUIWidget.h"
#include "CGUIFontWidget.h"
#include "CGUIImageWidget.h"

class CGUIEngine;
class CApplication;

class CTextSection {
   public:
   std::vector<std::string> Text;
   int Current;
   int End;

   bool setToTextWidgets(std::vector<CGUIFontWidget*> const &);
};

class CGUIDialogWidget : public CGUIWidget
{
   std::vector<CTextSection*> TextSections;
   std::vector<CGUIFontWidget*> Text;
   CGUIImageWidget *Board;
   CGUIEngine *Engine;
   int CurrentTextSection, Live;
   void loadDialogFile(std::string const &);

public:
	CGUIDialogWidget(std::string const & DialogFileName);

	void draw();

   void start();
   void next();
   void end();

   bool isLive();

	static std::string DialogDirectory;
};

#endif
