
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

			SharedPointer<Graphics::CUniformValue<color3f>> Color = std::make_shared<Graphics::CUniformValue<color3f>>();
			SharedPointer<Graphics::CUniformValue<float>> Radius = std::make_shared<Graphics::CUniformValue<float>>();

		};

	}
}
