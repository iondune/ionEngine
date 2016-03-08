
#include "CDirectionalLight.h"


namespace ion
{
	namespace Scene
	{

		CDirectionalLight::CDirectionalLight()
		{
			Attributes["Color"] = Color;
			Attributes["Direction"] = Direction;
		}

		color3f CDirectionalLight::GetColor() const
		{
			return *Color;
		}

		vec3f CDirectionalLight::GetDirection() const
		{
			return *Direction;
		}

		void CDirectionalLight::SetColor(color3f const & Color)
		{
			*(this->Color) = Color;
		}

		void CDirectionalLight::SetDirection(vec3f const & Direction)
		{
			*(this->Direction) = Direction;
		}

		string CDirectionalLight::GetLightType() const
		{
			return "DirectionalLight";
		}

	}
}
