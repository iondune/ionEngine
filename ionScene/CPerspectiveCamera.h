
#pragma once

#include "CCamera.h"


namespace ion
{
	namespace Scene
	{

		class CPerspectiveCamera : public CCamera
		{

		public:

			CPerspectiveCamera(f32 const aspectRatio, f32 const nearPlane = 0.1f, f32 const farPlane = 100.f, f32 const focalLength = 0.13f);

			f32 GetFieldOfView() const;
			f32 GetFocalLength() const;
			f32 GetAspectRatio() const;

			void SetFieldOfView(f32 const fieldOfView);
			void SetFocalLength(f32 const focalLength);
			void SetAspectRatio(f32 const aspectRatio);

			void RecalculateProjectionMatrix();
			void Update();

		protected:

			f32 FocalLength;
			f32 AspectRatio;

		};

	}
}
