
#include "IIndexBuffer.h"


namespace ion
{
	namespace Graphics
	{

		template <>
		void IIndexBuffer::UploadData<byte>(vector<byte> const & Data)
		{
			UploadData(Data.data(), Data.size(), EValueType::UnsignedInt8);
		}

		template <>
		void IIndexBuffer::UploadData<uint16>(vector<uint16> const & Data)
		{
			UploadData(Data.data(), Data.size(), EValueType::UnsignedInt16);
		}

		template <>
		void IIndexBuffer::UploadData<uint32>(vector<uint32> const & Data)
		{
			UploadData(Data.data(), Data.size(), EValueType::UnsignedInt32);
		}

	}
}
