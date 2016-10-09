
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
#ifdef _ION_CONFIG_REVERSE_DEPTH
			const float zNear = NearPlane;
			const float viewAngleVertical = GetFieldOfView();
			const float f = 1.0f / tan(viewAngleVertical / 2.0f); // 1.0 / tan(X) == cotangent(X)

			glm::mat4 projectionMatrix = {
				f / AspectRatio, 0.0f,  0.0f,  0.0f,
				0.0f,    f,  0.0f,  0.0f,
				0.0f, 0.0f,  0.0f, -1.0f,
				0.0f, 0.0f, zNear,  0.0f
			};

			ProjectionMatrix = projectionMatrix;
#else
			ProjectionMatrix = glm::perspective<f32>(, AspectRatio, NearPlane, FarPlane);
#endif
		}

		void CPerspectiveCamera::Update()
		{
			CCamera::Update();
			RecalculateProjectionMatrix();
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
