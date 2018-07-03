
#pragma once

#include <ionCore.h>

#include "IConstantBuffer.h"
#include "IInputLayout.h"


namespace ion
{
	namespace Graphics
	{

		struct EShaderType
		{
			enum
			{
				Vertex   = 0x001,
				Geometry = 0x002,
				Pixel    = 0x004,

				VertexPixel         = 0x005,
				VertexGeometryPixel = 0x007,
			};
		};

		//! \ingroup ionGraphics
		class IVertexStage
		{

		public:

			virtual ~IVertexStage() = default;

		};

		//! \ingroup ionGraphics
		class IGeometryStage
		{

		public:

			virtual ~IGeometryStage() = default;

		};

		//! \ingroup ionGraphics
		class IPixelStage
		{

		public:

			virtual ~IPixelStage() = default;

		};

		//! \ingroup ionGraphics
		class IShader
		{

		public:

			virtual ~IShader() = default;

			virtual void SetVertexStage(SharedPointer<IVertexStage> VertexShader) = 0;
			virtual void SetGeometryStage(SharedPointer<IGeometryStage> GeometryShader) = 0;
			virtual void SetPixelStage(SharedPointer<IPixelStage> PixelShader) = 0;

			virtual IConstantBuffer * GetConstantBuffer(string const & Name) = 0;
			virtual IInputLayout * CreateInputLayout(vector<SInputBufferLayout> const & Buffers) = 0;

			virtual void Link() = 0;

		};

	}
}
