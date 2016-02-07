
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

			vec3f const & GetPosition() const;
			void SetPosition(vec3f const & Position);

			size_t GetAttributeCount() const;
			Graphics::IUniform const * GetAttributeByName(string const & Name) const;

			virtual string const & GetLightType() const = 0;

		protected:

			vec3f Position;
			map<string, Graphics::IUniform *> Attributes;

		};

	}
}
