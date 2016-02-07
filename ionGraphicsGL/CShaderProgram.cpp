
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

			void CShaderProgram::Link()
			{
				CheckedGLCall(glBindFragDataLocation(Handle, 0, "outColor"));
				CheckedGLCall(glLinkProgram(Handle));

				int LinkStatus;
				CheckedGLCall(glGetProgramiv(Handle, GL_LINK_STATUS, & LinkStatus));

				if (LinkStatus)
				{
					Linked = true;

					// Load active uniforms
					int ActiveUniforms = 0;
					int ActiveUniformMaxLength = 0;
					CheckedGLCall(glGetProgramiv(Handle, GL_ACTIVE_UNIFORMS, & ActiveUniforms));
					CheckedGLCall(glGetProgramiv(Handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, & ActiveUniformMaxLength));
					for (int i = 0; i < ActiveUniforms; ++ i)
					{
						int Length = -1, Size = -1;
						uint DataType;
						char * Name = new char[ActiveUniformMaxLength + 1]();

						CheckedGLCall(glGetActiveUniform(Handle, i, ActiveUniformMaxLength, & Length, & Size, & DataType, Name));
						Uniforms[Name] = glGetUniformLocation(Handle, Name);
						delete[] Name;
					}

					// Load active attributes
					int ActiveAttributes = 0;
					int ActiveAttributeMaxLength = 0;
					CheckedGLCall(glGetProgramiv(Handle, GL_ACTIVE_ATTRIBUTES, & ActiveAttributes));
					CheckedGLCall(glGetProgramiv(Handle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, & ActiveAttributeMaxLength));
					for (GLint i = 0; i < ActiveAttributes; ++ i)
					{
						int Length = -1, Size = -1;
						uint DataType;
						char * Name = new char[ActiveAttributeMaxLength + 1];

						CheckedGLCall(glGetActiveAttrib(Handle, i, ActiveAttributeMaxLength, & Length, & Size, & DataType, Name));
						Attributes[Name] = glGetAttribLocation(Handle, Name);
						delete Name;
					}
				}

			}

		}
	}
}
