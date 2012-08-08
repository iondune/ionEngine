#include "CGUIFontWidget.h"

#include <iostream>

//#define OGLFT_NO_SOLID
//#define OGLFT_NO_QT
#include "liboglft/OGLFT.h"

#include "CGUIEngine.h"
#include "CApplication.h"

std::string CGUIFontWidget::FontDirectory = "../Media/Fonts/";

void CGUIFontWidget::makeRenderer(std::string const & FileName, float const Size)
{
	if (Renderer)
		delete Renderer;

	Renderer = new OGLFT::Translucent((FontDirectory + FileName).c_str(), Size);
	if (! Renderer)
	{
		std::cerr << "Failed to open ttf font file: '" << (FontDirectory + FileName) << "'." << std::endl;
	}

	if (! Renderer || ! Renderer->isValid())
	{
		if (Renderer)
		{
			delete Renderer;
			Renderer = 0;
		}

		std::cerr << "Could not construct face from " << FileName << std::endl;
		return;
	}
	Renderer->setBackgroundColor(0.f, 0.f, 0.f, 0.f);
	Renderer->setHorizontalJustification(OGLFT::Face::CENTER);
	Renderer->setVerticalJustification(OGLFT::Face::MIDDLE);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

CGUIFontWidget::CGUIFontWidget(std::string const & FileName, float const Size)
	: Renderer(0), DropShadow(0)
{
   FileNameString = FileName;
   FontSize = Size;

	makeRenderer(FileName, Size);
	setColor(SColorAf(0, 0, 0));
}

void CGUIFontWidget::draw()
{
	if (! Visible)
		return;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

	if (Renderer)
	{
		Renderer->setStringRotation(Rotation);
		Renderer->draw(Box.Position.X, Box.Position.Y, Text.c_str()); 
	}

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}

SColorAf const CGUIFontWidget::getDropShadowColor() {
   if(!DropShadow)
      return SColorAf(0.0f);
   else
      return DropShadow->getColor();
}

void CGUIFontWidget::addDropShadow() {
   addDropShadow(SColorAf(0.0f));   
}

void CGUIFontWidget::addDropShadow(SColorAf const & Color) {
   if(DropShadow) {
      removeDropShadow();
   }
   DropShadow = new CGUIFontWidget(FileNameString, FontSize);
   DropShadow->setText(Text);
   DropShadow->setVisible(true);

   DropShadow->setPosition(this->getPosition() + SVector2f(0.0f, -0.002f));
   DropShadow->setColor(Color);
   DropShadow->setVisible(Visible);
   //CApplication::get().getGUIEngine().addWidget(DropShadow);
}

void CGUIFontWidget::removeDropShadow() {
   if(DropShadow) {
      //CApplication::get().getGUIEngine().removeWidget(DropShadow);
      delete DropShadow;
      DropShadow = NULL;
   }
}

bool const CGUIFontWidget::hasDropShadow() {
   return !!DropShadow;
}

void CGUIFontWidget::setVisible(bool const visible)
{
	Visible = visible;
   if(DropShadow)
      DropShadow->setVisible(visible);
}

void CGUIFontWidget::setColor(SColorAf const & Color)
{
	if (Renderer)
		Renderer->setForegroundColor(Color.Red, Color.Green, Color.Blue, Color.Alpha);
}

SColorAf const CGUIFontWidget::getColor()
{
	return Renderer ? SColorAf(Renderer->foregroundRed(), Renderer->foregroundGreen(), Renderer->foregroundBlue(), Renderer->foregroundAlpha()) : SColorAf();
}

void CGUIFontWidget::setText(std::string const & text)
{
	Text = text;
	if (Renderer)
	{
		OGLFT::BBox BBox = Renderer->measure_nominal(text.c_str());
		Box.Size = SVector2f(BBox.x_max_ - BBox.x_min_, BBox.y_max_ - BBox.y_min_);
	}

   if(DropShadow)
      DropShadow->setText(Text);
}

std::string const & CGUIFontWidget::getText() const
{
	return Text;
}
