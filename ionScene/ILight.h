
#pragma once

#include <ionMath.h>
#include <ionGraphics.h>


namespace ion
{
	namespace Scene
	{

		class ILight
		{

		public:

			ILight();

			vec3f GetPosition() const;
			void SetPosition(vec3f const & Position);

			size_t GetAttributeCount() const;
			map<string, SharedPointer<Graphics::IUniform>> const & GetAttributes() const;
			SharedPointer<Graphics::IUniform const> GetAttributeByName(string const & Name) const;

			virtual string GetLightType() const = 0;

		protected:

			SharedPointer<Graphics::CUniformValue<vec3f>> Position = std::make_shared<Graphics::CUniformValue<vec3f>>();
			map<string, SharedPointer<Graphics::IUniform>> Attributes;

		};

	}
}
