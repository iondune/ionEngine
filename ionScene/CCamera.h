
#pragma once

#include "ICamera.h"


namespace ion
{
	namespace Scene
	{

		class CCamera : public ICamera
		{

		public:

			CCamera();

			virtual void RecalculateViewMatrix();
			virtual void Update();

			virtual vec3f const & GetPosition() const;
			virtual vec3f const & GetLookDirecton() const;
			virtual vec3f GetLookAtTarget() const;
			virtual vec3f const & GetUpVector() const;
			virtual glm::mat4 GetViewMatrix() const;
			virtual glm::mat4 GetProjectionMatrix() const;

			virtual void SetPosition(vec3f const & position);
			virtual void SetLookDirection(vec3f const & lookDirection);
			virtual void SetLookAtTarget(vec3f const & lookAtTarget);
			virtual void SetUpVector(vec3f const & UpVector);
			virtual void SetViewMatrix(glm::mat4 const & viewMatrix);
			virtual void SetProjectionMatrix(glm::mat4 const & projectionMatrix);

			virtual f32 GetNearPlane() const;
			virtual f32 GetFarPlane() const;
			virtual void SetNearPlane(f32 const nearPlane);
			virtual void SetFarPlane(f32 const farPlane);

			virtual vec2i GetScreenCoordinates(vec3f const & WorldPosition, vec2f const & WindowSize, bool * InFront = nullptr);
			virtual ray3f GetPickingRay(vec2i const & Pixel, vec2f const & WindowSize);

		protected:

			vec3f Position;
			vec3f LookDirection;
			vec3f UpVector;

			glm::mat4 ViewMatrix;
			glm::mat4 ProjectionMatrix;
			f32 NearPlane, FarPlane;

		};

	}
}
