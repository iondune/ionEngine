
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
			float const zNear = NearPlane;
			float const zFar = FarPlane;
			float const viewAngleVertical = GetFieldOfView();
			float const f = 1.0f / tan(viewAngleVertical / 2.0f); // 1.0 / tan(X) == cotangent(X)

			switch (ProjectionType)
			{
			case EProjectionType::Standard:
			{
				ProjectionMatrix = glm::perspective<f32>(viewAngleVertical, AspectRatio, NearPlane, FarPlane);
				break;
			}
			case EProjectionType::ReverseZeroToOne:
			{
				glm::mat4 projectionMatrix =
				{
					glm::vec4(f / AspectRatio, 0.0f,  0.0f,  0.0f),
					glm::vec4(0.0f,    f,  0.0f,  0.0f),
					glm::vec4(0.0f, 0.0f,  -zFar / (zNear - zFar) - 1, -1.0f),
					glm::vec4(0.0f, 0.0f, -(zNear * zFar) / (zNear - zFar),  0.0f)
				};
				ProjectionMatrix = projectionMatrix;

				break;
			}
			case EProjectionType::ReverseZeroToOneInfiniteFar:
			{
				glm::mat4 projectionMatrix = {
					f / AspectRatio, 0.0f,  0.0f,  0.0f,
					0.0f,    f,  0.0f,  0.0f,
					0.0f, 0.0f,  0.0f, -1.0f,
					0.0f, 0.0f, zNear,  0.0f
				};

				ProjectionMatrix = projectionMatrix;
				break;
			}
			}
		}

		void CPerspectiveCamera::Update()
		{
			CCamera::Update();
			RecalculateProjectionMatrix();
		}

		EProjectionType CPerspectiveCamera::GetProjectionType() const
		{
			return ProjectionType;
		}

		void CPerspectiveCamera::SetProjectionType(EProjectionType const Type)
		{
			ProjectionType = Type;
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
