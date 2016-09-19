
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
			ViewMatrix = glm::translate(glm::lookAt(glm::vec3(), LookDirection.ToGLM(), UpVector.ToGLM()), -GetPosition().ToGLM());
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

		vec2i CCamera::GetScreenCoordinates(vec3f const & WorldPosition, vec2f const & WindowSize, bool * InFront)
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

		ray3f CCamera::GetPickingRay(vec2i const & Pixel, vec2f const & WindowSize)
		{
			ray3f Ray;

			vec2f const NormalizedCursorPosition = (vec2f(Pixel)) / (vec2f(WindowSize) * 0.5f) - 1.f;

			glm::mat4 InverseViewProjection = glm::inverse(ProjectionMatrix * ViewMatrix);
			glm::vec4 ClipCoordinates = glm::vec4(NormalizedCursorPosition.X, -NormalizedCursorPosition.Y, -1, 1);
			glm::vec4 EyeCoordinates = glm::inverse(ProjectionMatrix) * ClipCoordinates;
			EyeCoordinates.z = -1;
			EyeCoordinates.w = 0;
			glm::vec4 WorldCoordinates = glm::inverse(ViewMatrix) * EyeCoordinates;

			Ray.Origin = Position;
			//Ray.Direction = Normalize(Right * Normalized.X - Up * Normalized.Y + View * FocalLength);
			Ray.Direction = vec3f::FromGLM(glm::vec3(WorldCoordinates)).GetNormalized();

			return Ray;
		}

	}
}
