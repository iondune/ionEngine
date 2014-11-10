
#include "COrthogonalCamera.h"


COrthogonalCamera::COrthogonalCamera(ISceneNode * Parent, f32 const left, f32 const right, f32 const bottom, f32 const top)
	: CCamera(Parent), Left(left), Right(right), Bottom(bottom), Top(top)
{}

void COrthogonalCamera::RecalculateProjectionMatrix()
{
	ProjectionMatrix = glm::ortho<f32>(Left, Right, Bottom, Top, NearPlane, FarPlane);
}

f32 COrthogonalCamera::GetLeft() const
{
	return Left;
}

f32 COrthogonalCamera::GetRight() const
{
	return Right;
}

f32 COrthogonalCamera::GetBottom() const
{
	return Bottom;
}

f32 COrthogonalCamera::GetTop() const
{
	return Top;
}

void COrthogonalCamera::SetRight(f32 const right)
{
	Right = right;
}

void COrthogonalCamera::SetLeft(f32 const left)
{
	Left = left;
}

void COrthogonalCamera::SetTop(f32 const top)
{
	Top = top;
}

void COrthogonalCamera::SetBottom(f32 const bottom)
{
	Bottom = bottom;
}
