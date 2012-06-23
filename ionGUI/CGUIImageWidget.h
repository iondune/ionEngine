#ifndef _CABBAGEGUI_CGUIIMAGEWIDGET_H_INCLUDED_
#define _CABBAGEGUI_CGUIIMAGEWIDGET_H_INCLUDED_

#include <string>

#include <SColor.h>
#include <CTexture.h>

#include "CGUIWidget.h"

class CGUIImageWidget : public CGUIWidget
{

	CTexture * Image;

public:

	CGUIImageWidget(CTexture * image, SVector2f const & size);
	CGUIImageWidget(CImage * image, SVector2f const & size);
	CGUIImageWidget(std::string const & imagePath, SVector2f const & size);

	void draw();

	CTexture const * const getImage() const;
	void setImage(CTexture * image);

	SVector2f const & getSize() const;
	void setSize(SVector2f const & size);

};

#endif
