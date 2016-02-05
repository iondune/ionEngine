
#include "CPointLight.h"


namespace ion
{
	namespace Scene
	{

		color3f CPointLight::GetColor() const
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

		string CPointLight::GetLightType() const
		{
			return "PointLight";
		}

	}
}
