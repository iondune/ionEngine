
#pragma once

#include "CCamera.h"


namespace ion
{
	namespace Scene
	{

		class COrthographicCamera : public CCamera
		{

		public:

			COrthographicCamera(float const size, float const aspectRatio);
			COrthographicCamera(float const left, float const right, float const bottom, float const top);

			float GetTop() const;
			float GetBottom() const;
			float GetLeft() const;
			float GetRight() const;

			void SetTop(float const top);
			void SetBottom(float const bottom);
			void SetLeft(float const left);
			void SetRight(float const right);

			float GetSize() const;
			void SetSize(float const size);

			void RecalculateProjectionMatrix();
			void Update();
			ray3f GetPickingRay(vec2i const & Pixel, vec2f const & WindowSize);

		protected:

			float Top = 1.f, Bottom = -1.f, Left = -1.f, Right = 1.f;
			float AspectRatio = 1.f;

		};

	}
}
