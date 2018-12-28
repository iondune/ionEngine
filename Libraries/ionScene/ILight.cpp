
#include "ILight.h"


namespace ion
{
	namespace Scene
	{

		ILight::ILight()
		{
			Attributes["Position"] = Position;
		}

		vec3f ILight::GetPosition() const
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

		map<string, SharedPointer<Graphics::IUniform>> const & ILight::GetAttributes() const
		{
			return Attributes;
		}

		SharedPointer<Graphics::IUniform> ILight::GetAttributeByName(string const & Name)
		{
			return ConditionalMapAccess(Attributes, Name);
		}

	}
}
