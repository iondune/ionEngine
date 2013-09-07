
#pragma once

#include <ionCore.h>
#include <ionMath.h>


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

			void Data(u32 const size, void const * const data,
				EAccessFrequency const accessFrequency = EAccessFrequency::Stream,
				EAccessNature const accessNature = EAccessNature::Draw);

			void SubData(u32 const size, u32 const offset, void const * const data);

			void Delete();
			~Buffer();

		protected:

			Buffer();

			void Bind();
			void Unbind();
			virtual u32 GetTarget() = 0;

			u32 Handle;
		};

		class VertexBuffer : public Buffer
		{
		protected:

			u32 GetTarget();
		};

		class IndexBuffer : Buffer
		{
		protected:

			u32 GetTarget();
		};
	}
}
