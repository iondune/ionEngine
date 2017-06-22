
#include "COrthographicCamera.h"


namespace ion
{
	namespace Scene
	{

		COrthographicCamera::COrthographicCamera(float const left, float const right, float const bottom, float const top)
			: Left(left), Right(right), Bottom(bottom), Top(top)
		{}

		void COrthographicCamera::RecalculateProjectionMatrix()
		{
			ProjectionMatrix = glm::ortho<float>(Left, Right, Bottom, Top, NearPlane, FarPlane);
		}

		void COrthographicCamera::Update()
		{
			CCamera::Update();
			RecalculateProjectionMatrix();
		}

		float COrthographicCamera::GetLeft() const
		{
			return Left;
		}

		float COrthographicCamera::GetRight() const
		{
			return Right;
		}

		float COrthographicCamera::GetBottom() const
		{
			return Bottom;
		}

		float COrthographicCamera::GetTop() const
		{
			return Top;
		}

		void COrthographicCamera::SetRight(float const right)
		{
			Right = right;
		}

		void COrthographicCamera::SetLeft(float const left)
		{
			Left = left;
		}

		void COrthographicCamera::SetTop(float const top)
		{
			Top = top;
		}

		void COrthographicCamera::SetBottom(float const bottom)
		{
			Bottom = bottom;
		}

	}
}
