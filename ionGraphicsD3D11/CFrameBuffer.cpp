
#include "CFrameBuffer.h"

#include "CTexture.h"
#include "CDepthBuffer.h"


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			CFrameBuffer::~CFrameBuffer()
			{
			}

			void CFrameBuffer::AttachColorTexture(SharedPointer<ITexture2D> Texture, uint const Attachment)
			{
			}

			void CFrameBuffer::AttachDepthTexture(SharedPointer<ITexture2D> Texture)
			{
			}

			void CFrameBuffer::AttachDepthBuffer(SharedPointer<IDepthBuffer> DepthBuffer)
			{
			}

			bool CFrameBuffer::CheckCorrectness()
			{
				return false;
			}

			void CFrameBuffer::Bind()
			{
			}

		}
	}
}
