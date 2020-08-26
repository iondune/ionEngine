
#pragma once

#include "CCamera.h"


namespace ion
{
	namespace Scene
	{

		enum class EProjectionType
		{
			Standard,
			ReverseZeroToOne,
			ReverseZeroToOneInfiniteFar
		};

		class CPerspectiveCamera : public CCamera
		{

		public:

			CPerspectiveCamera(float const aspectRatio, float const nearPlane = 0.1f, float const farPlane = 100.f, float const focalLength = 0.13f);

			float GetFieldOfView() const;
			float GetFocalLength() const;
			float GetAspectRatio() const;

			void SetFieldOfView(float const fieldOfView);
			void SetFocalLength(float const focalLength);
			void SetAspectRatio(float const aspectRatio);

			void RecalculateProjectionMatrix();
			void Update();

			EProjectionType GetProjectionType() const;
			void SetProjectionType(EProjectionType const Type);
			ray3f GetPickingRay(vec2f const & Pixel, vec2i const & WindowSize);

		protected:

			EProjectionType ProjectionType = EProjectionType::Standard;

			float FocalLength;
			float AspectRatio;

		};

	}
}
