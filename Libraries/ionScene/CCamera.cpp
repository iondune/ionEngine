
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
			ViewMatrix = glm::translate(glm::lookAt(glm::vec3(), GetLookDirecton().ToGLM(), UpVector.ToGLM()), -GetPosition().ToGLM());
		}

		void CCamera::Update()
		{
			RecalculateViewMatrix();
		}

		vec3f const & CCamera::GetPosition() const
		{
			return Position;
		}

		vec3f CCamera::GetLookDirecton() const
		{
			return DirectionMode ? LookDirection : LookTarget - Position;
		}

		vec3f CCamera::GetLookAtTarget() const
		{
			return DirectionMode ? Position + LookDirection : LookTarget;
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
			DirectionMode = true;
		}

		void CCamera::SetLookAtTarget(vec3f const & lookAtTarget)
		{
			LookTarget = lookAtTarget;
			DirectionMode = false;
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

		float CCamera::GetNearPlane() const
		{
			return NearPlane;
		}

		float CCamera::GetFarPlane() const
		{
			return FarPlane;
		}

		void CCamera::SetNearPlane(float const nearPlane)
		{
			NearPlane = nearPlane;
		}

		void CCamera::SetFarPlane(float const farPlane)
		{
			FarPlane = farPlane;
		}

		vec2i CCamera::GetScreenCoordinates(vec3f const & WorldPosition, vec2i const & WindowSize, bool * InFront)
		{
			vec4f WorldCoords = vec4f(WorldPosition.X, WorldPosition.Y, WorldPosition.Z, 1);
			WorldCoords.Transform(ViewMatrix);
			WorldCoords.Transform(ProjectionMatrix);

			vec2f ScreenCoords = WorldCoords.XY() / WorldCoords.W;

			if (InFront)
			{
				float const Z = (WorldCoords.Z / WorldCoords.W);
				*InFront = (Z > -1 && Z < 1);
			}

			ScreenCoords.Y *= -1;
			ScreenCoords += 1;
			ScreenCoords /= 2;
			ScreenCoords *= vec2f(WindowSize);

			return vec2i(ScreenCoords);
		}

	}
}
