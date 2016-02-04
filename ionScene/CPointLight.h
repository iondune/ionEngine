
#pragma once

#include "CLight.h"


namespace ion
{
	namespace Scene
	{

		class CPointLight
		{

		public:

			color3f const & GetColor() const;
			float GetRadius() const;

			void SetColor(color3f const & Color);
			void SetRadius(float const Radius);

			string const & GetLightType() const;

		protected:

			Graphics::CUniformValue<color3f> Color;
			Graphics::CUniformValue<float> Radius;

		};

	}
}
