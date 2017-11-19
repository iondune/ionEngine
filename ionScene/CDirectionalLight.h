
#pragma once

#include "ILight.h"


namespace ion
{
	namespace Scene
	{

		class CDirectionalLight : public ILight
		{

		public:

			CDirectionalLight();

			color3f GetColor() const;
			vec3f GetDirection() const;

			void SetColor(color3f const & Color);
			void SetDirection(vec3f const & Direction);

			string GetLightType() const;

		protected:

			Graphics::CUniform<color3f> Color = color3f(1.f);
			Graphics::CUniform<vec3f> Direction = vec3f(0, -1, 0);

		};

	}
}
