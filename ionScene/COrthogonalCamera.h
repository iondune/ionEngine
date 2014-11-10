
#pragma once

#include "CCamera.h"


class COrthogonalCamera : public CCamera
{

public:

	COrthogonalCamera(ISceneNode * Parent, f32 const left, f32 const right, f32 const bottom, f32 const top);

	f32 GetTop() const;
	f32 GetBottom() const;
	f32 GetLeft() const;
	f32 GetRight() const;

	void SetTop(f32 const top);
	void SetBottom(f32 const bottom);
	void SetLeft(f32 const left);
	void SetRight(f32 const right);

	void RecalculateProjectionMatrix();

protected:

	f32 Top, Bottom, Left, Right;

};
