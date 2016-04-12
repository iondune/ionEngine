
#include "CPerspectiveCamera.h"



namespace ion
{
	namespace Scene
	{

		CPerspectiveCamera::CPerspectiveCamera(f32 const aspectRatio, f32 const nearPlane, f32 const farPlane, f32 const focalLength)
			: AspectRatio(aspectRatio), FocalLength(focalLength)
		{
			this->NearPlane = nearPlane;
			this->FarPlane = farPlane;
		}

		void CPerspectiveCamera::RecalculateProjectionMatrix()
		{
			ProjectionMatrix = glm::perspective<f32>(GetFieldOfView(), AspectRatio, NearPlane, FarPlane);
		}

		void CPerspectiveCamera::Update()
		{
			CCamera::Update();
			RecalculateProjectionMatrix();
		}

		ray3f CPerspectiveCamera::GetPickingRay(vec2i const & Pixel, vec2f const & WindowSize)
		{
			ray3f Ray;

			vec2f const Normalized = (vec2f(Pixel)) / (vec2f(WindowSize) * 0.5f) - 1.f;

			glm::mat4 InverseViewProjection = glm::inverse(ProjectionMatrix * ViewMatrix);
			glm::vec4 ScreenCoordinates = glm::vec4(Normalized.X, -Normalized.Y, 1, 1);
			glm::vec4 WorldCoordinates = InverseViewProjection * ScreenCoordinates;

			Ray.Origin = Position;
			//Ray.Direction = Normalize(Right * Normalized.X - Up * Normalized.Y + View * FocalLength);
			Ray.Direction = vec3f::FromGLM(glm::vec3(WorldCoordinates)).GetNormalized();

			return Ray;
		}

		f32 CPerspectiveCamera::GetFieldOfView() const
		{
			return ArcTan(0.5f / FocalLength);
		}

		f32 CPerspectiveCamera::GetFocalLength() const
		{
			return FocalLength;
		}

		f32 CPerspectiveCamera::GetAspectRatio() const
		{
			return AspectRatio;
		}

		void CPerspectiveCamera::SetFocalLength(f32 const focalLength)
		{
			FocalLength = focalLength;
		}

		void CPerspectiveCamera::SetFieldOfView(f32 const fieldOfView)
		{
			FocalLength = 0.5f / Tan(fieldOfView);
		}

		void CPerspectiveCamera::SetAspectRatio(f32 const aspectRatio)
		{
			AspectRatio = aspectRatio;
		}

	}
}
