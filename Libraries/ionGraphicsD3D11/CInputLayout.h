
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>

#include <D3D11.h>


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			class CInputLayout : public IInputLayout
			{

			public:

				CInputLayout(ID3D11Device * Device, vector<SInputLayoutElement> const & LayoutElements, bool const Instancing);
				CInputLayout() = default;
				~CInputLayout();

				ID3D11InputLayout * InputLayout = nullptr;

			};

		}
	}
}
