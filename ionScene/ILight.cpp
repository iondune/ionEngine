
#include "ILight.h"


namespace ion
{
	namespace Scene
	{

		vec3f const & ILight::GetPosition() const
		{
			return Position;
		}

		void ILight::SetPosition(vec3f const & Position)
		{
			this->Position = Position;
		}

		size_t ILight::GetAttributeCount() const
		{
			return Attributes.size();
		}

		Graphics::IUniform const * ILight::GetAttributeByName(string const & Name) const
		{
			return ConditionalMapAccess(Attributes, Name);
		}

	}
}
