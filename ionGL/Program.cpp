
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
			
			int Linked;
			CheckedGLCall(glGetProgramiv(Handle, GL_LINK_STATUS, & Linked));
			if (! Linked)
				return false;

			// Load active uniforms
			int ActiveUniforms = 0;
			int ActiveUniformMaxLength = 0;
			glGetProgramiv(Handle, GL_ACTIVE_UNIFORMS, & ActiveUniforms);
			glGetProgramiv(Handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, & ActiveUniformMaxLength);
			for (int i = 0; i < ActiveUniforms; ++ i)
			{
				int Length = -1, Size = -1;
				uint DataType;
				char * Name = new char[ActiveUniformMaxLength + 1]();

				glGetActiveUniform(Handle, i, ActiveUniformMaxLength, & Length, & Size, & DataType, Name);
				Uniforms[Name] = glGetUniformLocation(Handle, Name);
				delete [] Name;
			}

			// Load active attributes
			int ActiveAttributes = 0;
			int ActiveAttributeMaxLength = 0;
			glGetProgramiv(Handle, GL_ACTIVE_ATTRIBUTES, & ActiveAttributes);
			glGetProgramiv(Handle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, & ActiveAttributeMaxLength);
			for (GLint i = 0; i < ActiveAttributes; ++ i)
			{
				int Length = -1, Size = -1;
				uint DataType;
				char * Name = new char[ActiveAttributeMaxLength + 1];

				glGetActiveAttrib(Handle, i, ActiveAttributeMaxLength, & Length, & Size, & DataType, Name);
				Attributes[Name] = glGetAttribLocation(Handle, Name);
				delete Name;
			}

			return true;
		}

		std::string Program::InfoLog() const
		{
			std::string Log;
			int InfoLogLength = 0;
			int CharsWritten = 0;
			
			CheckExistingErrors(Program::InfoLog);
			glGetProgramiv(Handle, GL_INFO_LOG_LENGTH, & InfoLogLength);

			if (OpenGLError())
			{
				cerr << "Error occured during glGetProgramiv: " << GetOpenGLError() << endl;
				cerr << "Handle is " << Handle << endl;
				cerr << endl;
			}
			else if (InfoLogLength > 0)
			{
				GLchar * InfoLog = new GLchar[InfoLogLength];
				glGetProgramInfoLog(Handle, InfoLogLength, & CharsWritten, InfoLog);
				Log = InfoLog;
				delete[] InfoLog;
			}

			return Log;
		}

		void Program::BindAttributeLocation(u32 const index, string const name)
		{
			CheckedGLCall(glBindAttribLocation(Handle, index, name.c_str()));
		}

		std::map<std::string, u32> const & Program::GetActiveAttributes()
		{
			return Attributes;
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
