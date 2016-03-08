
#include "IIndexBuffer.h"


namespace ion
{
	namespace Graphics
	{

		template <>
		void IIndexBuffer::UploadData<u8>(vector<u8> const & Data)
		{
			UploadData(Data.data(), Data.size(), EValueType::UnsignedInt8);
		}

		template <>
		void IIndexBuffer::UploadData<u16>(vector<u16> const & Data)
		{
			UploadData(Data.data(), Data.size(), EValueType::UnsignedInt16);
		}

		template <>
		void IIndexBuffer::UploadData<u32>(vector<u32> const & Data)
		{
			UploadData(Data.data(), Data.size(), EValueType::UnsignedInt32);
		}

	}
}
