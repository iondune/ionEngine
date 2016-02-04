
#include "CLight.h"


namespace ion
{
	namespace Scene
	{

		vec3f const & CLight::GetPosition() const
		{
			return Position;
		}

		void CLight::SetPosition(vec3f const & Position)
		{
			this->Position = Position;
		}

		uint CLight::GetAttributeCount() const
		{
			return Attributes.size();
		}

		Graphics::IUniform const * CLight::GetAttributeByName(string const & Name) const
		{
			return ConditionalMapAccess(Attributes, Name);
		}

	}
}
