
#include "Shader.h"
#include "Utilities.h"
#include <GL/glew.h>


namespace ion
{
	namespace GL
	{
		////////////
		// Shader //
		////////////

		void Shader::Source(std::vector<std::string> const & Source)
		{
			c8 const ** Lines = new c8 const *[Source.size()];
			for (u32 i = 0; i < Source.size(); ++ i)
				Lines[i] = Source[i].c_str();
			CheckedGLCall(glShaderSource(Handle, (int) Source.size(), Lines, 0));
		}

		void Shader::Source(std::string const & Source)
		{
			c8 const * Line = Source.c_str();
			CheckedGLCall(glShaderSource(Handle, 1, & Line, 0));
		}

		bool Shader::Compile()
		{
			CheckedGLCall(glCompileShader(Handle));

			s32 Compiled;
			CheckedGLCall(glGetShaderiv(Handle, GL_COMPILE_STATUS, & Compiled));

			return Compiled != 0;
		}

		std::string Shader::InfoLog() const
		{
			std::string Log;
			int InfoLogLength = 0;
			int CharsWritten = 0;
			
			CheckExistingErrors(Shader::InfoLog);
			glGetShaderiv(Handle, GL_INFO_LOG_LENGTH, & InfoLogLength);

			if (OpenGLError())
			{
				cerr << "Error occured during glGetShaderiv: " << GetOpenGLError() << endl;
				cerr << "Handle is " << Handle << endl;
				cerr << endl;
			}
			else if (InfoLogLength > 0)
			{
				GLchar * InfoLog = new GLchar[InfoLogLength];
				glGetShaderInfoLog(Handle, InfoLogLength, & CharsWritten, InfoLog);
				Log = InfoLog;
				delete[] InfoLog;
			}

			return Log;
		}

		void Shader::Delete()
		{
			delete this;
		}

		Shader::~Shader()
		{
			glDeleteShader(Handle);
		}

		Shader::Shader(u32 const handle)
			: Handle(handle)
		{}


		//////////////
		// Variants //
		//////////////

#ifdef GL_COMPUTE_SHADER
		ComputeShader::ComputeShader()
			: Shader(glCreateShader(GL_COMPUTE_SHADER))
		{}
#endif

		VertexShader::VertexShader()
			: Shader(glCreateShader(GL_VERTEX_SHADER))
		{}

		TesselationControlShader::TesselationControlShader()
			: Shader(glCreateShader(GL_TESS_CONTROL_SHADER))
		{}

		TesselationEvaluationShader::TesselationEvaluationShader()
			: Shader(glCreateShader(GL_TESS_EVALUATION_SHADER))
		{}

		GeometryShader::GeometryShader()
			: Shader(glCreateShader(GL_GEOMETRY_SHADER))
		{}

		FragmentShader::FragmentShader()
			: Shader(glCreateShader(GL_FRAGMENT_SHADER))
		{}
	}
}
