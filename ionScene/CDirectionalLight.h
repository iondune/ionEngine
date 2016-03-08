
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

			SharedPtr<Graphics::CUniformValue<color3f>> Color = std::make_shared<Graphics::CUniformValue<color3f>>();
			SharedPtr<Graphics::CUniformValue<vec3f>> Direction = std::make_shared<Graphics::CUniformValue<vec3f>>();

		};

	}
}
