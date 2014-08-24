
#pragma once

#include <ionCore.h>
#include <ionMath.h>


namespace ion
{
	namespace GL
	{
		enum EBuffer
		{
			Color = 0,
			Depth = 1,
			Stencil = 2
		};

		class Context
		{
		public:

			static void Init();
			static void Clear(std::initializer_list<EBuffer> Buffers = { EBuffer::Color, EBuffer::Depth });

			static vec2i GetViewportSize();

		};
	}
}
