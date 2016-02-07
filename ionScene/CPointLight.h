
#pragma once

#include "ILight.h"


namespace ion
{
	namespace Scene
	{

		class CPointLight
		{

		public:

			color3f GetColor() const;
			float GetRadius() const;

			void SetColor(color3f const & Color);
			void SetRadius(float const Radius);

			string GetLightType() const;

		protected:

			Graphics::CUniformValue<color3f> Color;
			Graphics::CUniformValue<float> Radius;

		};

	}
}
