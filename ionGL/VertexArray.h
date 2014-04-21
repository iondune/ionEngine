
#pragma once

#include <ionCore.h>
#include <ionMath.h>

#include "Utilities.h"
#include "Buffer.h"


namespace ion
{
	namespace GL
	{
		class VertexArray
		{
		public:

			VertexArray();

			void SetIndexBuffer(IndexBuffer * ibo);
			void BindAttribute(u32 const index, VertexBuffer * vbo);
			void Draw();
			
			void Delete();
			~VertexArray();

		protected:
			
			u32 Handle;
			EPrimativeType PrimativeType;
			IndexBuffer * BoundIndexBuffer;

		};
	}
}
