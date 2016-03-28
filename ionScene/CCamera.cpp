
#include "CCamera.h"


namespace ion
{
	namespace Scene
	{

		CCamera::CCamera()
		{
			this->LookDirection = vec3f(0, 0, 1);
			this->UpVector = vec3f(0, 1, 0);
			this->NearPlane = 0.1f;
			this->FarPlane = 100.f;

			RecalculateViewMatrix();
		}

		void CCamera::RecalculateViewMatrix()
		{
			ViewMatrix = glm::lookAt(GetPosition().ToGLM(), (GetPosition() + LookDirection).ToGLM(), UpVector.ToGLM());
		}

		void CCamera::Update()
		{
			RecalculateViewMatrix();
		}

		vec3f const & CCamera::GetPosition() const
		{
			return Position;
		}

		vec3f const & CCamera::GetLookDirecton() const
		{
			return LookDirection;
		}

		vec3f CCamera::GetLookAtTarget() const
		{
			return GetPosition() + LookDirection;
		}

		vec3f const & CCamera::GetUpVector() const
		{
			return UpVector;
		}

		void CCamera::SetPosition(vec3f const & position)
		{
			Position = position;
		}

		void CCamera::SetLookDirection(vec3f const & lookDirection)
		{
			LookDirection = lookDirection;
		}

		void CCamera::SetLookAtTarget(vec3f const & lookAtTarget)
		{
			SetLookDirection(lookAtTarget - GetPosition());
		}

		void CCamera::SetUpVector(vec3f const & upVector)
		{
			UpVector = upVector;
		}

		glm::mat4 CCamera::GetViewMatrix() const
		{
			return ViewMatrix;
		}

		glm::mat4 CCamera::GetProjectionMatrix() const
		{
			return ProjectionMatrix;
		}

		void CCamera::SetViewMatrix(glm::mat4 const & viewMatrix)
		{
			ViewMatrix = viewMatrix;
		}

		void CCamera::SetProjectionMatrix(glm::mat4 const & projectionMatrix)
		{
			ProjectionMatrix = projectionMatrix;
		}

		f32 CCamera::GetNearPlane() const
		{
			return NearPlane;
		}

		f32 CCamera::GetFarPlane() const
		{
			return FarPlane;
		}

		void CCamera::SetNearPlane(f32 const nearPlane)
		{
			NearPlane = nearPlane;
		}

		void CCamera::SetFarPlane(f32 const farPlane)
		{
			FarPlane = farPlane;
		}

	}
}
