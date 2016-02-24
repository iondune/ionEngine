
#pragma once

#include <ionCore.h>


namespace ion
{
	namespace Graphics
	{

		class IVertexShader
		{

		public:

			virtual ~IVertexShader() {}

		};

		class IPixelShader
		{

		public:

			virtual ~IPixelShader() {}

		};

		class IShaderProgram
		{

		public:

			virtual void SetVertexStage(SharedPtr<IVertexShader> VertexShader) = 0;
			virtual void SetPixelStage(SharedPtr<IPixelShader> PixelShader) = 0;

		};

	}
}
