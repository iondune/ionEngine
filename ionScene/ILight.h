
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
			map<string, SharedPtr<Graphics::IUniform>> const & GetAttributes() const;
			SharedPtr<Graphics::IUniform const> GetAttributeByName(string const & Name) const;

			virtual string GetLightType() const = 0;

		protected:

			SharedPtr<Graphics::CUniformValue<vec3f>> Position = std::make_shared<Graphics::CUniformValue<vec3f>>();
			map<string, SharedPtr<Graphics::IUniform>> Attributes;

		};

	}
}
