
#pragma once

#include "color3.h"
#include "color4.h"


namespace ion
{

	namespace Color
	{

		//! \brief Some very basic colors
		//! \ingroup ionMath
		struct Basic
		{
			static color3f const White;
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
		//! \ingroup ionMath
		static uint PackBits24(color3i const & Color)
		{
			uint const Red = Color.Red;
			uint const Green = Color.Green;
			uint const Blue = Color.Blue;
			return (Red << 16) | (Green << 8) | (Blue);
		}

		//! \brief Unacks a color from 24 bits
		//! \ingroup ionMath
		static color3i UnpackBits24(uint const Value)
		{
			color3i Color;
			Color.Red = (Value >> 16) & 0xFF;
			Color.Green = (Value >> 8) & 0xFF;
			Color.Blue = Value & 0xFF;
			return Color;
		}

	}

}
