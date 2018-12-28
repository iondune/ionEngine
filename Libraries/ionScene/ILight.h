
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
			SharedPointer<Graphics::IUniform> GetAttributeByName(string const & Name);

			virtual string GetLightType() const = 0;

		protected:

			Graphics::CUniform<vec3f> Position;
			map<string, SharedPointer<Graphics::IUniform>> Attributes;

		};

	}
}
