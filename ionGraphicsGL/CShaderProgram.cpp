
#include "CShaderProgram.h"

#include "Utilities.h"
#include "CVertexShader.h"
#include "CPixelShader.h"

#include <GL/glew.h>


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{
			
			void CShaderProgram::SetVertexStage(IVertexShader * VertexShader)
			{
				CheckedGLCall(glAttachShader(Handle, dynamic_cast<CVertexShader *>(VertexShader)->Handle));
			}

			void CShaderProgram::SetPixelStage(IPixelShader * PixelShader)
			{
				CheckedGLCall(glAttachShader(Handle, dynamic_cast<CPixelShader *>(PixelShader)->Handle));
			}

			void CShaderProgram::SetInputLayout(SInputLayoutElement * InputLayout, int const NumElements)
			{
				this->InputLayout.clear();

				for (int i = 0; i < NumElements; ++ i)
				{
					this->InputLayout.push_back(InputLayout[i]);
				}
			}

			void CShaderProgram::Link()
			{
				CheckedGLCall(glBindFragDataLocation(Handle, 0, "outColor"));
				CheckedGLCall(glLinkProgram(Handle));

				Linked = true;
			}

		}
	}
}
