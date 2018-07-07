
#include "COrthographicCamera.h"


namespace ion
{
	namespace Scene
	{

		COrthographicCamera::COrthographicCamera(float const Size, float const AspectRatio)
		{
			Left = -Size / 2 * AspectRatio;
			Right = Size / 2 * AspectRatio;
			Top = Size / 2;
			Bottom = -Size / 2;
		}

		COrthographicCamera::COrthographicCamera(float const left, float const right, float const bottom, float const top)
			: Left(left), Right(right), Bottom(bottom), Top(top)
		{}

		void COrthographicCamera::RecalculateProjectionMatrix()
		{
			ProjectionMatrix = glm::mat4(1.f);
			ProjectionMatrix[0][0] = (2.f) / (Right - Left);
			ProjectionMatrix[1][1] = (2.f) / (Top - Bottom);
			ProjectionMatrix[3][0] = - (Right + Left) / (Right - Left);
			ProjectionMatrix[3][1] = - (Top + Bottom) / (Top - Bottom);

			ProjectionMatrix[2][2] = 1.f / (NearPlane - FarPlane);
			ProjectionMatrix[3][2] = (NearPlane) / (NearPlane - FarPlane);
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
