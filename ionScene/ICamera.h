
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

			virtual void Update() = 0;

		};

	}
}
