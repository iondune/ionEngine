
#pragma once

#include "CCamera.h"


class CPerspectiveCamera : public CCamera
{

public:

	CPerspectiveCamera(f32 const aspectRatio = 16.f/9.f, f32 const nearPlane = 0.1f, f32 const farPlane = 100.f, f32 const focalLength = 1.f);

	f32 GetFieldOfView() const;
	f32 GetFocalLength() const;
	f32 GetAspectRatio() const;
	f32 GetNearPlane() const;
	f32 GetFarPlane() const;

	void SetFieldOfView(f32 const fieldOfView);
	void SetFocalLength(f32 const focalLength);
	void SetAspectRatio(f32 const aspectRatio);
	void SetNearPlane(f32 const nearPlane);
	void SetFarPlane(f32 const farPlane);

	void UpdateProjectionMatrix();

protected:

	f32 FocalLength;
	f32 AspectRatio;
	f32 NearPlane, FarPlane;

};
