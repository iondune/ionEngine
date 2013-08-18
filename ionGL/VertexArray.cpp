#include "ionGL.h"
#include "Utilities.h"


namespace ion
{
	namespace GL
	{
		VertexArray::VertexArray()
		{
			glGenVertexArrays(1, & Handle);
		}

		void VertexArray::Delete()
		{
			delete this;
		}

		VertexArray::~VertexArray()
		{
			glDeleteVertexArrays(1, & Handle);
		}
	}
}
