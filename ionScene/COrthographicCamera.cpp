
#include "COrthographicCamera.h"


namespace ion
{
	namespace Scene
	{

		COrthographicCamera::COrthographicCamera(f32 const left, f32 const right, f32 const bottom, f32 const top)
			: Left(left), Right(right), Bottom(bottom), Top(top)
		{}

		void COrthographicCamera::RecalculateProjectionMatrix()
		{
			ProjectionMatrix = glm::ortho<f32>(Left, Right, Bottom, Top, NearPlane, FarPlane);
		}

		void COrthographicCamera::Update()
		{
			CCamera::Update();
			RecalculateProjectionMatrix();
		}

		f32 COrthographicCamera::GetLeft() const
		{
			return Left;
		}

		f32 COrthographicCamera::GetRight() const
		{
			return Right;
		}

		f32 COrthographicCamera::GetBottom() const
		{
			return Bottom;
		}

		f32 COrthographicCamera::GetTop() const
		{
			return Top;
		}

		void COrthographicCamera::SetRight(f32 const right)
		{
			Right = right;
		}

		void COrthographicCamera::SetLeft(f32 const left)
		{
			Left = left;
		}

		void COrthographicCamera::SetTop(f32 const top)
		{
			Top = top;
		}

		void COrthographicCamera::SetBottom(f32 const bottom)
		{
			Bottom = bottom;
		}

	}
}
