
#pragma once

#include "CCamera.h"


namespace ion
{
	namespace Scene
	{

		class COrthographicCamera : public CCamera
		{

		public:

			COrthographicCamera(float const Size, float const AspectRatio);
			COrthographicCamera(float const left, float const right, float const bottom, float const top);

			float GetTop() const;
			float GetBottom() const;
			float GetLeft() const;
			float GetRight() const;

			void SetTop(float const top);
			void SetBottom(float const bottom);
			void SetLeft(float const left);
			void SetRight(float const right);

			void RecalculateProjectionMatrix();
			void Update();

		protected:

			float Top, Bottom, Left, Right;

		};

	}
}
