
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
			virtual vec3f GetLookDirecton() const;
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

			virtual float GetNearPlane() const;
			virtual float GetFarPlane() const;
			virtual void SetNearPlane(float const nearPlane);
			virtual void SetFarPlane(float const farPlane);

			virtual vec2i GetScreenCoordinates(vec3f const & WorldPosition, vec2i const & WindowSize, bool * InFront = nullptr);
			virtual ray3f GetPickingRay(vec2f const & Pixel, vec2i const & WindowSize) = 0;

		protected:

			vec3f Position;
			vec3f UpVector;

			bool DirectionMode = true;

			glm::mat4 ViewMatrix;
			glm::mat4 ProjectionMatrix;
			float NearPlane, FarPlane;

		private:

			vec3f LookDirection;
			vec3f LookTarget;

		};

	}
}
