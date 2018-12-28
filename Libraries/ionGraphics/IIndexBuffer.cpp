
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
		void IIndexBuffer::UploadData<Uint16>(vector<Uint16> const & Data)
		{
			UploadData(Data.data(), Data.size(), EValueType::UnsignedInt16);
		}

		template <>
		void IIndexBuffer::UploadData<Uint32>(vector<Uint32> const & Data)
		{
			UploadData(Data.data(), Data.size(), EValueType::UnsignedInt32);
		}

	}
}
