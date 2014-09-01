
#pragma once

#include <ionCore.h>
#include <ionMath.h>

#include "Utilities.h"


namespace ion
{
	namespace GL
	{
		class Buffer
		{
			friend class VertexArray;

		public:

			enum class EAccessFrequency
			{
				Stream = 0,
				Static = 1,
				Dynamic = 2
			};

			enum class EAccessNature
			{
				Draw = 0,
				Read = 1,
				Copy = 2
			};

			template <typename T>
			void Data(vector<T> data, u32 const components,
				EAccessFrequency const accessFrequency = EAccessFrequency::Stream,
				EAccessNature const accessNature = EAccessNature::Draw)
			{
				Data(data.size() * sizeof(T), data.data(), components, accessFrequency, accessNature);
			}

			template <typename T>
			void Data(u32 const size, T const * const data, u32 const components,
				EAccessFrequency const accessFrequency = EAccessFrequency::Stream,
				EAccessNature const accessNature = EAccessNature::Draw);

			template <typename T>
			void SubData(vector<T> data, u32 const offset = 0)
			{
				SubData(data.size() * sizeof(T), offset * sizeof(T), data.data());
			}

			void SubData(u32 const size, u32 const offset, void const * const data);

			u32 Size() const;
			u32 Elements() const;
			u32 Components() const;
			EFormatType Type() const;

			void Delete();
			virtual ~Buffer();

		protected:

			Buffer();

			void Bind();
			void Unbind();

			void InternalData(u32 const size, void const * const data, u32 const components,
				EAccessFrequency const accessFrequency = EAccessFrequency::Stream,
				EAccessNature const accessNature = EAccessNature::Draw);

			virtual u32 GetTarget() = 0;

			u32 Handle;
			u32 DataSize;
			u32 DataComponents;
			EFormatType DataType;
		};

		class VertexBuffer : public Buffer
		{
		protected:

			u32 GetTarget();
		};

		class IndexBuffer : public Buffer
		{
		public:

			template <typename T>
			void Data(u32 const size, T const * const data,
				EAccessFrequency const accessFrequency = EAccessFrequency::Stream,
				EAccessNature const accessNature = EAccessNature::Draw)
			{
				Buffer::Data(size, data, 1, accessFrequency, accessNature);
			}

			template <typename T>
			void Data(vector<T> data,
				EAccessFrequency const accessFrequency = EAccessFrequency::Stream,
				EAccessNature const accessNature = EAccessNature::Draw)
			{
				Buffer::Data(data, 1, accessFrequency, accessNature);
			}

		protected:

			u32 GetTarget();
		};
	}
}
