
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

			void AttributePointer(VertexBuffer * Buffer, u32 const index, u32 const size, EFormatType const type, u32 const stride = 0, void * offset = 0);

			void EnableAttribute(u32 const index);
			void DisableAttribute(u32 const index);
			
			void Delete();
			~VertexArray();

		protected:
			
			u32 Handle;
		};
	}
}
