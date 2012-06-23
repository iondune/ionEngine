#include "CGUIImageWidget.h"

#include <CTextureLoader.h>

CGUIImageWidget::CGUIImageWidget(CImage * image, SVector2f const & size)
	: Image(new CTexture(image))
{
	Box.Size = size;
}

CGUIImageWidget::CGUIImageWidget(CTexture * image, SVector2f const & size)
	: Image(image)
{
	Box.Size = size;
}

CGUIImageWidget::CGUIImageWidget(std::string const & imagePath, SVector2f const & size)
	: Image(CTextureLoader::loadTexture(imagePath))
{
	Box.Size = size;
}


void CGUIImageWidget::draw()
{
	if (! Visible || ! Image)
		return;

	glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Image->getTextureHandle());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslatef(Box.Position.X + Box.Size.X / 2.f, Box.Position.Y + Box.Size.Y / 2.f, 0.f);
	glRotatef(Rotation, 0, 0, 1);
	glTranslatef(-Box.Size.X / 2.f, -Box.Size.Y / 2.f, 0.f);
	glScalef(Box.Size.X, Box.Size.Y, 1.f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	glBegin(GL_QUADS);
		glTexCoord2i(0, 0);
		glVertex2i(0, 0);

		glTexCoord2i(1, 0);
		glVertex2i(1, 0);

		glTexCoord2i(1, 1);
		glVertex2i(1, 1);

		glTexCoord2i(0, 1);
		glVertex2i(0, 1);
	glEnd();

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}


CTexture const * const CGUIImageWidget::getImage() const
{
	return Image;
}

void CGUIImageWidget::setImage(CTexture * image)
{
	Image = image;
}


SVector2f const & CGUIImageWidget::getSize() const
{
	return Box.Size;
}

void CGUIImageWidget::setSize(SVector2f const & size)
{
	Box.Size = size;
}
