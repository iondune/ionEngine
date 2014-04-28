
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

			int ActiveUniforms = 0;
			int ActiveUniformMaxLength = 0;
			glGetProgramiv(Handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, & ActiveUniformMaxLength);
			glGetProgramiv(Handle, GL_ACTIVE_UNIFORMS, & ActiveUniforms);
			for (int i = 0; i < ActiveUniforms; ++ i)
			{
				GLsizei Length = -1, Size = -1;
				GLenum dataType;
				char * Name = new char[ActiveUniformMaxLength + 1]();
				glGetActiveUniform(Handle, i, ActiveUniformMaxLength, & Length, & Size, & dataType, Name);
				uint Location = glGetUniformLocation(Handle, Name);
				Uniforms[Name] = Location;
				delete [] Name;
			}

			return true;
		}

		void Program::BindAttributeLocation(u32 const index, string const name)
		{
			CheckedGLCall(glBindAttribLocation(Handle, index, name.c_str()));
		}

		std::map<std::string, u32> const & Program::GetActiveUniforms()
		{
			return Uniforms;
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
