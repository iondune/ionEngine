
#pragma once

#include <ionCore.h>


namespace ion
{
	namespace Graphics
	{

		//! \ingroup ionGraphics
		class IVertexShader
		{

		public:

			virtual ~IVertexShader() {}

		};

		//! \ingroup ionGraphics
		class IGeometryShader
		{

		public:

			virtual ~IGeometryShader() {}

		};

		//! \ingroup ionGraphics
		class IPixelShader
		{

		public:

			virtual ~IPixelShader() {}

		};

		//! \ingroup ionGraphics
		class IShaderProgram
		{

		public:

			virtual void SetVertexStage(SharedPointer<IVertexShader> VertexShader) = 0;
			virtual void SetGeometryStage(SharedPointer<IGeometryShader> GeometryShader) = 0;
			virtual void SetPixelStage(SharedPointer<IPixelShader> PixelShader) = 0;

		};

	}
}
