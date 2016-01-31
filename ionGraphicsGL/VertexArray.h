
#pragma once

#if 0

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>

#include "Utilities.h"
#include "Buffer.h"


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{

			class VertexArray
			{
			public:

				VertexArray(EPrimitiveType const PrimitiveType = EPrimitiveType::Triangles);

				void SetIndexBuffer(IIndexBuffer * ibo);
				void SetElementCount(uint count);
				void BindAttribute(u32 const index, IVertexBuffer * vbo);
				void Draw();

				void Delete();
				~VertexArray();

			protected:

				u32 Handle = 0;
				uint ElementCount = 0;
				EPrimitiveType PrimitiveType;
				IIndexBuffer * BoundIndexBuffer = nullptr;

			};

		}
	}
}

#endif
