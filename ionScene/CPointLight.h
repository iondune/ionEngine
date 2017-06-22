
#pragma once

#include "ILight.h"


namespace ion
{
	namespace Scene
	{

		class CPointLight : public ILight
		{

		public:

			CPointLight();

			color3f GetColor() const;
			float GetRadius() const;

			void SetColor(color3f const & Color);
			void SetRadius(float const Radius);

			string GetLightType() const;

		protected:

			Graphics::CUniform<color3f> Color = 1.f;
			Graphics::CUniform<float> Radius = 20.f;

		};

	}
}
