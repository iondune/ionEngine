
#pragma once

#include <ionCore.h>

#include "Enums.h"


namespace ion
{
	namespace Graphics
	{

		//! \ingroup ionGraphics
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

		//! \ingroup ionGraphics
		class IVertexBuffer
		{

		public:

			virtual ~IVertexBuffer()
			{}

			template <typename T>
			void UploadData(vector<T> const & Data)
			{
				UploadData(Data.data(), sizeof(T), Data.size());
			}

			template <typename T>
			void UploadSubData(vector<T> const & Data, size_t const Offset)
			{
				UploadSubData(Data.data(), sizeof(T), Offset, Data.size());
			}

			virtual void UploadData(void const * const Data, size_t const DataSize, size_t const NumberOfElements) = 0;
			virtual void UploadSubData(void const * const Data, size_t const DataSize, size_t const Offset, size_t const NumberOfElements) = 0;

			virtual void SetInputLayout(SInputLayoutElement const * const InputLayout, int const NumElements) = 0;

		};

		//! \ingroup ionGraphics
		class IInstanceBuffer
		{

		public:

			virtual ~IInstanceBuffer()
			{}

			template <typename T>
			void UploadData(vector<T> const & Data)
			{
				UploadData(Data.data(), sizeof(T), Data.size());
			}

			template <typename T>
			void UploadSubData(vector<T> const & Data, size_t const Offset)
			{
				UploadSubData(Data.data(), sizeof(T), Offset, Data.size());
			}

			virtual void UploadData(void const * const Data, size_t const DataSize, size_t const NumberOfElements) = 0;
			virtual void UploadSubData(void const * const Data, size_t const DataSize, size_t const Offset, size_t const NumberOfElements) = 0;

			virtual void SetInputLayout(SInputLayoutElement const * const InputLayout, int const NumElements) = 0;

			virtual void SetInstanceCount(int const InstanceCount) = 0;

		};
	}
}
