
#include "Shader.h"
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
			glShaderSource(Handle, Source.size(), Lines, 0);
		}

		void Shader::Source(std::string const & Source)
		{
			c8 const * Line = Source.c_str();
			glShaderSource(Handle, 1, & Line, 0);
		}

		bool Shader::Compile()
		{
			glCompileShader(Handle);

			s32 Compiled;
			glGetShaderiv(Handle, GL_COMPILE_STATUS, & Compiled);

			return Compiled != 0;
		}

		std::string Shader::InfoLog() const
		{
			std::string Log;
			int InfoLogLength = 0;
			int CharsWritten = 0;

			glGetShaderiv(Handle, GL_INFO_LOG_LENGTH, & InfoLogLength);

			if (InfoLogLength > 0)
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

		ComputeShader::ComputeShader()
			: Shader(glCreateShader(GL_COMPUTE_SHADER))
		{}

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
