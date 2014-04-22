
#include "Program.h"
#include <GL/glew.h>


namespace ion
{
	namespace GL
	{
		Program::Program()
			: Handle(glCreateProgram())
		{}

		Program::~Program()
		{
			CheckedGLCall(glDeleteProgram(Handle));
			for (auto shader : AttachedShaders)
				delete shader;
		}

		void Program::AttachShader(Shader * shader)
		{
			CheckedGLCall(glAttachShader(Handle, shader->Handle));
			AttachedShaders.push_back(shader);
		}

		bool Program::Link()
		{
			CheckedGLCall(glBindFragDataLocation(Handle, 0, "outColor"));
			CheckedGLCall(glLinkProgram(Handle));

			return true;
		}

		void Program::BindAttributeLocation(u32 const index, string const name)
		{
			CheckedGLCall(glBindAttribLocation(Handle, index, name.c_str()));
		}

		void Program::Use()
		{
			CheckedGLCall(glUseProgram(Handle));
		}

		void Program::End()
		{
			CheckedGLCall(glUseProgram(0));
		}
	}
}
