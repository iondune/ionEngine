
#include "CPointLight.h"


namespace ion
{
	namespace Scene
	{

		color3f const & CPointLight::GetColor() const
		{
			return Color;
		}

		float CPointLight::GetRadius() const
		{
			return Radius;
		}

		void CPointLight::SetColor(color3f const & Color)
		{
			this->Color = Color;
		}

		void CPointLight::SetRadius(float const Radius)
		{
			this->Radius = Radius;
		}

		string const & CPointLight::GetLightType() const
		{
			return "PointLight";
		}

	}
}
