
#pragma once

#include "color3.h"
#include "color4.h"


namespace ion
{

	namespace Color
	{

		extern color3f const White;
		extern color3f const Black;

		//! \brief Some very basic colors
		//! \ingroup ionCore
		struct Basic
		{
			static color3f const White;
			static color3f const Grey;
			static color3f const Black;
			static color3f const Red;
			static color3f const Orange;
			static color3f const Yellow;
			static color3f const Green;
			static color3f const Cyan;
			static color3f const Blue;
			static color3f const Magenta;
		};

		//! \brief Packs a color into 24 bits
		//! \ingroup ionCore
		uint PackBits24(color3i const & Color);

		//! \brief Unpacks a color from 24 bits
		//! \ingroup ionCore
		color3i UnpackBits24(uint const Value);

		//! \brief Unpacks a color from 24 bits
		//! \ingroup ionCore
		color3i Hex(uint const Value);

		//! \brief Compute RGB color from HSV
		//! \ingroup ionCore
		color3f HSV(float const H, float const S, float const V);

		//! \brief Compute RGB color from HSV
		//! \ingroup ionCore
		vec3f ToHSV(color3f const & Color);

	}

}
