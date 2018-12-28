
#pragma once

#include <ionCore.h>

#include "IUniform.h"


namespace ion
{
	namespace Graphics
	{

		//! \ingroup ionGraphics
		class IConstantBuffer
		{

		public:

			virtual ~IConstantBuffer() = default;

			virtual void SetUniform(string const & Name, SharedPointer<IUniform> Uniform) = 0;
			virtual bool OfferUniform(string const & Name, SharedPointer<IUniform> Uniform) = 0;

			virtual void Synchronize() = 0;

		};

	}
}
