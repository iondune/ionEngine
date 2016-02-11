
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
			map<string, Graphics::IUniform *> const & GetAttributes() const;
			Graphics::IUniform const * GetAttributeByName(string const & Name) const;

			virtual string GetLightType() const = 0;

		protected:

			Graphics::CUniformValue<vec3f> Position;
			map<string, Graphics::IUniform *> Attributes;

		};

	}
}
