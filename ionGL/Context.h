
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
			static void Clear(std::vector<EBuffer> Buffers = { EBuffer::Color, EBuffer::Depth });
			static void SetClearColor(color4f const & Color);

			static vec2i GetViewportSize();

		};
	}
}
