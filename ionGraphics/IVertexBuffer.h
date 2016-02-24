
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
			EAttributeType Type = EAttributeType::Float;

			SInputLayoutElement(string const & Name, int const Components, EAttributeType const Type)
			{
				this->Name = Name;
				this->Components = Components;
				this->Type = Type;
			}
		};

		class IVertexBuffer
		{

		public:

			virtual ~IVertexBuffer()
			{}

			virtual void UploadData(float const * const Data, size_t const Elements) = 0;

			virtual void SetInputLayout(SInputLayoutElement * InputLayout, int const NumElements) = 0;

			virtual void SetInstancingEnabled(bool const Enabled) = 0;

		};

	}
}
