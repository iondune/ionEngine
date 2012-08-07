#include "CGUIDialogWidget.h"
#include "CGUIEngine.h"
#include "CApplication.h"

std::string CGUIDialogWidget::DialogDirectory = "../Media/Dialogs/";

void CGUIDialogWidget::loadDialogFile(std::string const & FileName) {
   std::ifstream input((CGUIDialogWidget::DialogDirectory + FileName).c_str());
   if(!input.is_open()) {
      std::cerr << "Unable to open dialog file: " << FileName << std::endl;
      exit(1);
   }

   std::string line;
   CTextSection *current = NULL;
   std::vector<std::string> * currentText;
   while(input.good()) {
      std::getline(input, line);

      if(line.compare("SECTION") == 0) {
         if(current) {
            TextSections.push_back(current);
            current = NULL;
         }
         current = new CTextSection();
         currentText = &(current->Text);
         current->End = current->Current = 0;
         printf("Started a new section\n");
      }
      else if(line.compare("") == 0) {
         printf("Ignored a new line\n");
      }
      else {
         //TODO: Put a loop here to handle newlines
         currentText->push_back(line);
         printf("Added a new line to the section: %s\n", line.c_str());
         current->End += 1;
      }
   }
   TextSections.push_back(current);
}

CGUIDialogWidget::CGUIDialogWidget(std::string const & DialogFileName) {
   Engine = &(CApplication::get().getGUIEngine());
   loadDialogFile(DialogFileName);

   SPosition2 size = CApplication::get().getWindowSize();
   float aspectRatio = (float)size.X/(float)size.Y;
   // aspectRatio is the width in 1-space
   // so the side margins should be: (aspectRatio - widthOfBoardIn1Space)2

   float widthOfBoard = 1.0f;
   float heightOfBoard = 0.3f*widthOfBoard;
   float padding = widthOfBoard*0.05f;
   Board = new CGUIImageWidget(new CTexture(CImageLoader::loadTGAImage("MainMenu/wood.tga")), SVector2f(widthOfBoard, heightOfBoard));
   Board->setPosition(SVector2f((aspectRatio - widthOfBoard)/2.0f, padding));
   Board->setVisible(false);
   Engine->addWidget(Board);

   SVector2f bottomLeftOfBoard((aspectRatio - widthOfBoard)/2.0f, padding);

   int i;
   for(i = 0; i < 3; i++) {
      SVector2f textPosition = bottomLeftOfBoard + SVector2f(padding, (float)(2 - i)/(4.0f/heightOfBoard) + padding*1.5f);
      CGUIFontWidget *t = new CGUIFontWidget("WIFFLES_.TTF", 14.f/heightOfBoard);
      t->setVisible(false);
      t->setText("unset");
      t->setPosition(textPosition);
      t->setColor(SColorAf(1.0f));
      Text.push_back(t);
      Engine->addWidget(t);
   }
   CurrentTextSection = 0;
   Live = 1;
}

void CGUIDialogWidget::draw() {
	if (! Visible)
		return;
   Board->draw();
   for(int i = 0; i < 3; i++) {
      Text[i]->draw();
   }
}

bool CTextSection::setToTextWidgets(std::vector<CGUIFontWidget*> const & widgets) {
   End = Text.size() - widgets.size();
   if(End < 0)
      End = 0;
   if(Current > End)
      return false;
   for(unsigned int i = 0; i < widgets.size(); i++) {
      if(i + Current < Text.size())
         widgets[i]->setText(Text[i + Current]);
      else {
         widgets[i]->setText(" ");
      }
   }
   Current++;
   return true;
}

void CGUIDialogWidget::start() {
   Board->setVisible(true);
   for(int i = 0; i < 3; i++) {
      Text[i]->setVisible(true);
   }
   //Display current = 0 (i.e. the first 3 lines of the first section)
   TextSections[CurrentTextSection]->setToTextWidgets(Text);
}

void CGUIDialogWidget::next() {
   if(!Live)
      return;
   if(CurrentTextSection >= (int) TextSections.size()) {
      end();
      return;
   }
   if(!TextSections[CurrentTextSection]->setToTextWidgets(Text)) {
      CurrentTextSection++;
      next();
   }
}

void CGUIDialogWidget::end() {
   for(int i = 0; i < 3; i++) {
      Text[i]->setVisible(false);
      Engine->removeWidget(Text[i]);
   }
   Board->setVisible(false);
   Engine->removeWidget(Board);
   Live = 0;
}

bool CGUIDialogWidget::isLive() {
   return Live == 1;
}
