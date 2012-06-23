#include "CGUIWidget.h"

CGUIWidget::CGUIWidget()
	: Rotation(0.f), Visible(true), Hovered(false)
{}

SVector2f const & CGUIWidget::getPosition() const
{
	return Box.Position;
}

void CGUIWidget::setPosition(SVector2f const & position)
{
	Box.Position = position;
}

float const CGUIWidget::getRotation() const
{
	return Rotation;
}

void CGUIWidget::setRotation(float  const rotation)
{
	Rotation = rotation;
}

void CGUIWidget::draw()
{}

bool const CGUIWidget::isVisible() const
{
	return Visible;
}

bool const CGUIWidget::isHovered() const
{
	return Hovered;
}

void CGUIWidget::setVisible(bool const visible)
{
	Visible = visible;
}

SRect2f const & CGUIWidget::getBoundingBox() const
{
	return Box;
}
