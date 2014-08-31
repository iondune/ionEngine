
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

			VertexArray(EPrimativeType const PrimativeType = EPrimativeType::Triangles);
			
			void SetIndexBuffer(IndexBuffer * ibo);
			void SetElementCount(uint count);
			void BindAttribute(u32 const index, VertexBuffer * vbo);
			void Draw();
			
			void Delete();
			~VertexArray();

		protected:
			
			u32 Handle = 0;
			uint ElementCount = 0;
			EPrimativeType PrimativeType;
			IndexBuffer * BoundIndexBuffer = nullptr;

		};
	}
}
