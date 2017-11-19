
#pragma once

#include <ionCore.h>


namespace ion
{
	namespace Graphics
	{

		//! \ingroup ionGraphics
		class IVertexStage
		{

		public:

			virtual ~IVertexStage() {}

		};

		//! \ingroup ionGraphics
		class IGeometryStage
		{

		public:

			virtual ~IGeometryStage() {}

		};

		//! \ingroup ionGraphics
		class IPixelStage
		{

		public:

			virtual ~IPixelStage() {}

		};

		//! \ingroup ionGraphics
		class IShader
		{

		public:

			virtual void SetVertexStage(SharedPointer<IVertexStage> VertexShader) = 0;
			virtual void SetGeometryStage(SharedPointer<IGeometryStage> GeometryShader) = 0;
			virtual void SetPixelStage(SharedPointer<IPixelStage> PixelShader) = 0;

		};

	}
}
