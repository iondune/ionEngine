
#pragma once

#include <ionMath.h>


namespace ion
{
	namespace Scene
	{

		class ICamera
		{

		public:

			virtual glm::mat4 GetViewMatrix() const = 0;
			virtual glm::mat4 GetProjectionMatrix() const = 0;
			virtual vec3f const & GetPosition() const = 0;
			virtual vec3f const & GetLookDirecton() const = 0;
			virtual vec3f GetLookAtTarget() const = 0;
			virtual vec3f const & GetUpVector() const = 0;

			virtual void SetPosition(vec3f const & position) = 0;
			virtual void SetUpVector(vec3f const & UpVector) = 0;
			virtual void SetLookDirection(vec3f const & lookDirection) = 0;
			virtual void SetLookAtTarget(vec3f const & lookAtTarget) = 0;

			virtual void Update() = 0;

		};

	}
}
