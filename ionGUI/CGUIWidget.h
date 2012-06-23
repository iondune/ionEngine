#ifndef _CABBAGEGUI_CGUIWIDGET_H_INCLUDED_
#define _CABBAGEGUI_CGUIWIDGET_H_INCLUDED_

#include <SVector2.h>
#include <SRect2.h>

class CGUIWidget
{

protected:

	SRect2f Box;
	float Rotation;

	bool Visible;
	bool Hovered;

	friend class CGUIEngine;

public:

	CGUIWidget();

	SVector2f const & getPosition() const;
	void setPosition(SVector2f const & position);

	float const getRotation() const;
	void setRotation(float  const rotation);

	virtual void draw();

	bool const isVisible() const;
	virtual void setVisible(bool const visible);
	bool const isHovered() const;

	SRect2f const & getBoundingBox() const;

};

#endif
