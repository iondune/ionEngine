
#pragma once

#include <ionCore.h>

#include "Enums.h"


namespace ion
{
	namespace Graphics
	{

		struct SInputLayoutElement
		{
			string Name = "";
			int Components = 1;
			EValueType Type = EValueType::Float;

			SInputLayoutElement(string const & Name, int const Components, EValueType const Type)
			{
				this->Name = Name;
				this->Components = Components;
				this->Type = Type;
			}
		};

		class IVertexBuffer
		{

		public:

			virtual ~IVertexBuffer() {}
			virtual void SetInputLayout(SInputLayoutElement * InputLayout, int const NumElements) = 0;

		};

		class IIndexBuffer
		{

		public:

			virtual ~IIndexBuffer() {}

		};

	}
}
